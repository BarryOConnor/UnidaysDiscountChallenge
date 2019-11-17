#pragma once
#include <vector>

// Enumerated type which is human readable, expandable and easy to code for when it comes to adding new deals
enum saleTypes { NO_DISCOUNT, TWO_FOR_SET_PRICE, THREE_FOR_SET_PRICE, BOGOF, THREE_FOR_TWO };


struct basketItem {
	char itemName;
	int count;

	basketItem(char _itemName) {
		itemName = _itemName;
		count = 1;
	}
};

struct CheckoutTotals {
	/*==================================
	structure for returning checkout information
	==================================*/
	float Total;  //Order total
	float DeliveryCharge;  //Delivery charge for the order

	//default constructor
	CheckoutTotals() {
		//set values to 0 by default when the struct is created
		Total = 0.00;
		DeliveryCharge = 0.00;
	};

	// default constructor. No specific action needed
	~CheckoutTotals() {};
};

struct pricingRule {
	/*==================================
	structure to hold pricing rules
	==================================*/
	char item;
	float unitPrice;
	saleTypes discountType;
	float discountPrice;  //Order total

	//default constructor
	pricingRule() {
		//set values to 0 by default when the struct is created
		item = '\0';
		unitPrice = 0.00;
		discountType = NO_DISCOUNT;
		discountPrice = 0.00;  //Order total
	};

	pricingRule(char _item, float _unitPrice, saleTypes _discountType, float _discountPrice = 0.00) {
		//set values to 0 by default when the struct is created
		item = _item;
		unitPrice = _unitPrice;
		discountType = _discountType;
		discountPrice = _discountPrice;  //Order total
		if (_discountPrice < 0.00) {
			printf("discountPrice parameter should not be a negative number \n");
			exit(1);
		}
		else if (_discountPrice < 0.01 && (_discountType == TWO_FOR_SET_PRICE || _discountType == THREE_FOR_SET_PRICE)) {
			printf("this discount type requires a price in the fourth parameter \n");
			exit(1);
		};
	};

	// default constructor. No specific action needed
	~pricingRule() {};
};


class UnidaysDiscountChallenge{
	std::vector<pricingRule> pricingRules;
	std::vector<basketItem> basket;

public:
	UnidaysDiscountChallenge();
	UnidaysDiscountChallenge(std::vector<pricingRule>& _pricingRules);
	~UnidaysDiscountChallenge();

	bool AddToBasket(char _item);
	CheckoutTotals CalculateTotalPrice();
};



