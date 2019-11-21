#include <cstdio>
#include <stdlib.h>
#include <vector>

#include "UnidaysDiscountChallenge.h"


int main()
{
	CheckoutTotals result; //create a variable of the struct CheckoutTotals to store the results
	float totalPrice, deliveryCharge, overallTotal; // some floats to hold the values for the final printout
	
	/*-----
	Created a vector on the fly in this example by passing the values directly into the method to save a little memory
	but you could create a vector and add the rules in the following manner - slightly more readable for a large set of rules

	std::vector<pricingRule> appPricingRules;
	appPricingRules.push_back({ 'A', 8.00, NONE});
	appPricingRules.push_back({ 'B', 12.00, TWO_FOR, 20.00 });
	appPricingRules.push_back({ 'C', 4.00, THREE_FOR, 10.00 });
	appPricingRules.push_back({ 'D', 7.00, BOGOF });
	appPricingRules.push_back({ 'E', 5.00, THREE_FOR_TWO });

	-----*/
	UnidaysDiscountChallenge example({{ 'A', 8.00, NONE },{ 'B', 12.00, TWO_FOR, 20.00 },{ 'C', 4.00, THREE_FOR, 10.00 },{ 'D', 7.00, BOGOF },{ 'E', 5.00, THREE_FOR_TWO }});

	//add some items to the basket
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

	
	//return the results of the price calculation
	result = example.CalculateTotalPrice();

	//used as per the suggested example
	totalPrice = result.Total;
	deliveryCharge = result.DeliveryCharge;
	overallTotal = totalPrice + deliveryCharge;

	//print out the results
	printf("Subtotal: %4.2f \n", totalPrice);
	printf("Delivery Charge: %4.2f \n", deliveryCharge);
	printf("Overall Total: %4.2f \n", overallTotal);


	/*-----
	I created and inculded a test helper class in the code so that it was easier to run tests on the class.
	This would normally be in a second header and cpp file but for this purpose it made sense to just include it
	with the rest of the code.


	testclass testing;
	testing.doTest("A", 8.00, 7.00);
	testing.doTest("B", 12.00, 7.00);
	testing.doTest("C", 4.00, 7.00);
	testing.doTest("D", 7.00, 7.00);
	testing.doTest("E", 5.00, 7.00);
	testing.doTest("BB", 20.00, 7.00);
	testing.doTest("BBB", 32.00, 7.00);
	testing.doTest("BBBB", 40.00, 7.00);
	testing.doTest("CCC", 10.00, 7.00);
	testing.doTest("CCCC", 14.00, 7.00);
	testing.doTest("DD", 7.00, 7.00);
	testing.doTest("DDD", 14.00, 7.00);
	testing.doTest("EE", 10.00, 7.00);
	testing.doTest("EEE", 10.00, 7.00);
	testing.doTest("EEEE", 15.00, 7.00);
	testing.doTest("DDDDDDDDDDDDDD", 49.00, 7.00);
	testing.doTest("BBBBCCC", 50.00, 0.00);
	testing.doTest("ABBCCCDDEE", 55.00, 0.00);
	testing.doTest("EDCBAEDCBC", 55.00, 0.00); */

}