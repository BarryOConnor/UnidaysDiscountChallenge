#include <cstdio>
#include <cctype>
#include <stdlib.h>
#include <vector>
#include <algorithm>

#include "UnidaysDiscountChallenge.h"

UnidaysDiscountChallenge::UnidaysDiscountChallenge() {}

UnidaysDiscountChallenge::UnidaysDiscountChallenge(std::vector<pricingRule>& _pricingRules) {
	this->pricingRules = _pricingRules;
}

UnidaysDiscountChallenge::~UnidaysDiscountChallenge() {}



bool UnidaysDiscountChallenge::AddToBasket(char _item) {
	char itemToAdd;

	//capitalise the letter for ease of comparison and use
	itemToAdd = toupper(_item);
	
	/* ----- sanity check to see if the item has a corresponding priceRule -----*/
	//predicate lambda to check for the presence of a specific item within the pricing rules
	auto ruleResult = std::find_if(pricingRules.begin(), pricingRules.end(), [&itemToAdd](pricingRule const& currRule) { return currRule.item == itemToAdd; });

	if (ruleResult == pricingRules.end()) {
		//no pricing rule found, create error message
		printf("Error: This item does not have a pricing rule assigned to it, unable to add it to the basket\n");
		exit(1);
	}

	//convert the item name to uppercase
	//check if the item is a letter
	if (itemToAdd >= 'A' && itemToAdd <= 'Z') {
		//predicate lambda to check for the presence of a specific item within the shopping basket
		auto basketResult = std::find_if(basket.begin(), basket.end(), [&itemToAdd](basketItem const& currItem) { return currItem.itemName == itemToAdd; });
		if (basketResult != basket.end()) {
			//item exists so just increase the counter
			basketResult->count++;
			return true;
		}
		else {
			//item does not yet exist, so create it
			basket.push_back({ itemToAdd });
			return true;
		}
	}
	else {
		printf("Error: Item should be a character between A and Z\n");
		exit(1);
	}
}


CheckoutTotals UnidaysDiscountChallenge::CalculateTotalPrice() {
	CheckoutTotals checkoutResult;
	char currItemName;

	if (basket.size() == 0) {
		//basket is empty so return 0.00 for both values
		checkoutResult.Total = 0.00;
		checkoutResult.DeliveryCharge = 0.00;
	}
	else {
		checkoutResult.Total = 0.00;
		//iterate through the basket
		for (std::vector<basketItem>::iterator currItem = basket.begin(); currItem != basket.end(); ++currItem) {
			//set the current item so we can access it via the pointer in the predicate function
			currItemName = currItem->itemName;

			//predicate lambda to check for the presence of a specific item within the pricing rules
			auto ruleResult = std::find_if(pricingRules.begin(), pricingRules.end(), [&currItemName](pricingRule const& currRule) { return currRule.item == currItemName; });

			if (ruleResult != pricingRules.end()) {
				//rule exists - Expected
				//already checked for a corresponding priceRule so there's no need to check again here
				//at this point the items in the basket will all have a matching pricing rule
				
				//apply the correct price per item depending on the discount type
				switch (ruleResult->discountType) {
					case NO_DISCOUNT:
						//NO_DISCOUNT = multiply the number of items by the price per item
						checkoutResult.Total += currItem->count * ruleResult->unitPrice;
						break;
					case TWO_FOR_SET_PRICE:
						//TWO_FOR_SET_PRICE = for every 2, cost is equal to the discounted price. Add to that any remainder at the unit price
						checkoutResult.Total += (((currItem->count / 2) * ruleResult->discountPrice) + ((currItem->count % 2) * ruleResult->unitPrice));
						break;
					case THREE_FOR_SET_PRICE:
						//THREE_FOR_SET_PRICE = for every 3, cost is equal to the discounted price. Add to that any remainder at the unit price
						checkoutResult.Total += (((currItem->count / 3) * ruleResult->discountPrice) + ((currItem->count % 3) * ruleResult->unitPrice)) ;
						break;
					case BOGOF:
						//BOGOF = for every 2, cost is equal to 1. Add to that any remainder
						checkoutResult.Total += ((currItem->count / 2) + (currItem->count % 2)) * ruleResult->unitPrice;
						break;
					case THREE_FOR_TWO:
						//THREE_FOR_TWO = for every 3, cost is equal to 2 times the unit price. Add to that any remainder at the unit price
						checkoutResult.Total += (((currItem->count / 3) * (ruleResult->unitPrice * 2)) + ((currItem->count % 3) * ruleResult->unitPrice));
						break;
					default:
						//sanity check if none of the above match, assume price is no discount
						checkoutResult.Total += currItem->count * ruleResult->unitPrice;
						break;
				}
			}
		}

		/* ----- Delivery charge rules ----- */
		
		//set the value to 7.00 as default
		checkoutResult.DeliveryCharge = 7.00;
		if (checkoutResult.Total >= 50.00) {
			//delivery is free so for over 50 so set the delivery charge to 0.00
			checkoutResult.DeliveryCharge = 0.00;
		}

	}
	return checkoutResult;
}
