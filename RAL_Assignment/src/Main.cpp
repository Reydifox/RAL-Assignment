#include <iostream>
#include <vector>
#include <iterator>
#include <map>

#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include <NTL/ZZ_pX.h>
#include <NTL/ZZ_pXFactoring.h>

#include <Permutation.h>
#include <CSV.h>

NTL_CLIENT

void getMinPoly(StringArray &seq, std::vector<ZZ_pX> &out, int len)
{
	for (int s = 0; s < seq.size(); s++) 
	{
		vec_ZZ_p vec;
		vec.SetLength(len);

		for (int i = 0; i < len; i++)
		{
			vec.put(i, conv<ZZ_p>(seq.at(s).at(i)));
		}
		ZZ_pX poly = MinPolySeq(vec, !(len%2)?(len/2):(len-1)/2);
		out.push_back(poly);
	}
}

int main()
{
	cout << "Zadaj pole p (F2 -> 2): ";
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

	// Compute minimal polynomial from given sequence
	vector<ZZ_pX> polynomials;
	getMinPoly(arr, polynomials, length);

	// Get deg from polynomial
	vector<int> table(length+1, 0);
	for (int i = 0; i < polynomials.size(); i++)
	{
		int deg_p = deg(polynomials.at(i));
		table.at(deg_p) += 1;
	}

	// Print result
	for (int i = 0; i < 33; i++) cout << "_";
	cout << endl << "|" << "Stupen\t\t" << "|Pocet polynomov|" << endl;
	for (int i = 0; i < 33; i++) cout << "-";
	cout << endl;

	for (int i = 0; i < table.size(); i++)
	{
		cout << "|" << i << "\t\t" << "|" << table.at(i) << "\t\t" << "|" << endl;
	}
	for (int i = 0; i < 33; i++) cout << "-";
	cout << endl;

	// TODO generate CSV
	CSV csv;
	for (int i = 0; i < table.size(); i++)
	{
		Entity ent;
		ent.first = "Stupen";
		ent.second = std::to_string(i);
		csv.addData(ent);

		ent.first = "Pocet polynomov";
		ent.second = std::to_string(table.at(i));
		csv.addData(ent);
	}
	csv.save("distribution.csv");

    system("pause");
	return 0;
}