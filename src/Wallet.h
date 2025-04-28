#pragma once

#include <string>
#include <map>
#include "OrderBookEntry.h"

class Wallet
{
private:
	std::map<std::string, double> currencies;
public:
	Wallet();
	/**inset currency to a wallet */
	void insertCurrency(std::string type, double amount);
	/**remove currency from a wallet */
	bool removeCurrency(std::string type, double amount);
	/**check if the wallet contain this much currency or more */
	bool containCurrency(std::string type, double amount);
	/**update the contents of the wallet 
	* assume the order was made by the owner of the wallet
	*/
	void processSale(OrderBookEntry& sale);
	/**check if the wallet can cope with this ask or bid */
	bool canFulfillOrder(OrderBookEntry order);

	/**generate string representation of the wallet */
	std::string toString();

	bool isEmpty();


};

