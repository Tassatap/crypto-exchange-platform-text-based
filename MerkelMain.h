#pragma once
#include <vector>
#include "OrderBookEntry.h"

class MerkelMain
{
private:
    void loadOrderbook();
    void printMenu();
    void printHelp();
    void printMarketStats();
    void enterOffer();
    void enterBid();
    void printWallet();
    void gotoNextTimeFrame();
    int  getUserOption();
    void processUserOption(int userOption);
    double computeAveragePrice(std::vector<OrderBookEntry>& entries);
    double computeLowPrice(std::vector<OrderBookEntry>& entries);
    double computeHighPrice(std::vector<OrderBookEntry>& entries);
    double computePriceSpread(std::vector<OrderBookEntry>& entries);
    std::vector<OrderBookEntry> orders;

public:
	MerkelMain();
    /** Call this to start the sim*/
    void init();
};
