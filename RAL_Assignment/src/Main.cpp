#include <iostream>
#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include <NTL/ZZ_pX.h>
#include <NTL/ZZ_pXFactoring.h>

#include <Permutation.h>

NTL_CLIENT


int main()
{
	std::string buf;
	Permutation::generateStringSequence(10, 2, buf, true);

	StringArray arr;
	Permutation::parseStringToArray(buf, arr);

    cout << "Zadaj okruh (Z2 -> 2): ";
    int field = 0;

    cin >> field;
	ZZ_p::init(conv<ZZ>(field));

	cout << "Zadaj polynom: ";
	ZZ_pX polynom;

	cin >> polynom;
	if (IterIrredTest(polynom))
		cout << "Irreducibilny";
	else
		cout << "Reducibilny";
	cout << endl;

    system("pause");
	return 0;
}