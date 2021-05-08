#include <iostream>
#include <vector>
#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include <NTL/ZZ_pX.h>
#include <NTL/ZZ_pXFactoring.h>

#include <Permutation.h>

NTL_CLIENT

void getMinPoly(StringArray &seq, std::vector<ZZ_pX> &out, int len, int field)
{
	for (int s = 0; s < seq.size(); s++) 
	{
		vec_ZZ_p vec;
		vec.SetLength(len);

		for (int i = 0; i < len; i++)
		{
			vec.put(i, conv<ZZ_p>(seq.at(s).at(i)));
		}
		ZZ_pX poly;
		MinPolySeq(poly, vec, field);
		out.push_back(poly);
	}
}

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
	Permutation::generateStringSequence(length, field, buf, false);

	// Parse buffer to the string array
	StringArray arr;
	Permutation::parseStringToArray(buf, arr);

	ZZ_p::init(conv<ZZ>(field));

	// TODO compute minimal polynomial from given sequence
	std::vector<ZZ_pX> polynomials;
	getMinPoly(arr, polynomials, length, field);

	for (const auto& p : polynomials)
	{
		cout << p << endl;
	}

	// TODO get coeff from polynomial
	// TODO generate CSV

    system("pause");
	return 0;
}