#pragma once

#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"

class MerkelMain
{
private:
    void printMenu();
    void printHelp();
    void printMarketStats();
    void enterAsk();
    void enterBid();
    void printWallet();
    void gotoNextTimeFrame();
    int  getUserOption();
    void processUserOption(int userOption);
    double computeAveragePrice(std::vector<OrderBookEntry>& entries);
    double computeLowPrice(std::vector<OrderBookEntry>& entries);
    double computeHighPrice(std::vector<OrderBookEntry>& entries);
    double computePriceSpread(std::vector<OrderBookEntry>& entries);

    std::string currentTime;

    OrderBook orderBook{"Crypto_trading_data.csv"};
public:
	MerkelMain();
    /** Call this to start the sim*/
    void init();
};
