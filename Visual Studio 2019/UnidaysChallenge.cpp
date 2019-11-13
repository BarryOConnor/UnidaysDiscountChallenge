#include <cstdio>
#include <stdlib.h>
#include <vector>

#include "UnidaysDiscountChallenge.h"

int main()
{
	std::vector<pricingRule> appPricingRules;
	CheckoutTotals result;
	float totalPrice, deliveryCharge, overallTotal;

	//initialise pricingRules with some values, it's a little neater to do this
	appPricingRules.push_back({ 'A', 8.00, NO_DISCOUNT });
	appPricingRules.push_back({ 'B', 12.00, TWO_FOR_SET_PRICE, 20.00 });
	appPricingRules.push_back({ 'C', 4.00, THREE_FOR_SET_PRICE, 10.00 });
	appPricingRules.push_back({ 'D', 7.00, BOGOF });
	appPricingRules.push_back({ 'E', 5.00, THREE_FOR_TWO });

	UnidaysDiscountChallenge example(appPricingRules);

	example.AddToBasket('E');
	example.AddToBasket('D');
	example.AddToBasket('C');
	example.AddToBasket('B');
	example.AddToBasket('A');
	example.AddToBasket('E');
	example.AddToBasket('D');
	example.AddToBasket('C');
	example.AddToBasket('B');
	example.AddToBasket('C');


	result = example.CalculateTotalPrice();

	totalPrice = result.Total;
	deliveryCharge = result.DeliveryCharge;
	overallTotal = totalPrice + deliveryCharge;

	printf("Subtotal: %4.2f \n", totalPrice);
	printf("Delivery Charge: %4.2f \n", deliveryCharge);
	printf("Overall Total: %4.2f \n", overallTotal);
}


