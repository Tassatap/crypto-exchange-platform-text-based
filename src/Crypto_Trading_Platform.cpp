#include <iostream>
#include <string>
#include <vector>
#include "OrderBookEntry.h"
#include "MerkelMain.h"
#include "CSVReader.h"
#include "Wallet.h"

int main()
{
    //Wallet wallet;
    //wallet.insertCurrency("BTC", 100);
    //std::cout << wallet.toString();
    MerkelMain app{};
    app.init();
}

