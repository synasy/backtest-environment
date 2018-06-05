
//
//  portfolio.hpp
//  Backtest Environment
//
//  Created by Evan Kirkiles on 6/2/18.
//  Copyright © 2018 Evan Kirkiles. All rights reserved.
//

#ifndef portfolio_hpp
#define portfolio_hpp

#include <stdio.h>
#ifndef Event
#include "events.hpp"
#endif

#include "data.hpp"

using namespace std;

// Abstract base portfolio class so cannot be instantiated directly
class Portfolio {
public:
    // Generate new signal based on portfolio logic
    virtual void update_signal(Event* event)=0;
    // Update portfolio current position and holdings
    virtual void update_fill(Event* event)=0;
};

// Placeholder 'naive' portfolio that has minimal logic behind its ordering
// Used to test simple strategies
class NaivePortfolio:Portfolio {
public:
    HistoricalCSVDataHandler bars;
    vector<Event> events;
    vector<string> symbol_list;
    long start_date;
    double initial_capital;
    
    map<long, map<string, double>> all_positions;
    map<string, double> current_positions;
    
    map<long, map<string, double>> all_holdings;
    map<string, double> current_holdings;
    
    // Initialization function
    NaivePortfolio(HistoricalCSVDataHandler i_bars, vector<string> i_symbol_list, vector<Event> i_events, long i_start_date, double i_initial_capital);
    
    // Functions to construct positions and holdings
    map<long, map<string, double>> construct_all_positions();
    map<string, double> construct_current_positions();
    map<long, map<string, double>> construct_all_holdings();
    map<string, double> construct_current_holdings();
    
    // Updates the holdings tracking
    void update_timeindex(Event event);
    
    // Receives a FillEvent and changes the positions and holdings to correctly reflect the event
    void update_positions_from_fill(FillEvent event);
    void update_holdings_from_fill(FillEvent event);
    
    // Parent portfolio functions
    void update_signal(Event* event);
    void update_fill(Event* event);
};

#endif /* portfolio_hpp */