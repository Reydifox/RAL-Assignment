#include <iostream>
#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include <NTL/ZZ_pX.h>
#include <NTL/ZZ_pXFactoring.h>

#include <Permutation.h>

NTL_CLIENT


int main()
{
	cout << "Zadaj okruh p (Z2 -> 2): ";
	int field = 0;
	cin >> field;

	cout << "Zadaj dlzku postupnosti n: ";
	int length = 0;
	cin >> length;

	// Generate and save sequences n mod p
	std::string buf;
	Permutation::generateStringSequence(length, field, buf, true);

	// Parse buffer to the string array
	StringArray arr;
	Permutation::parseStringToArray(buf, arr);

	ZZ_p::init(conv<ZZ>(field));

	// TODO compute minimal polynomial from given sequence
	// TODO get coeff from polynomial
	// TODO generate CSV

    system("pause");
	return 0;
}