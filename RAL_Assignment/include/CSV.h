#pragma once
#include <iostream>
#include <vector>
#include <fstream>

using Entity = std::pair < std::string, std::string >;
using EntSet = std::vector < Entity >;

class CSV
{
private:
	EntSet table;

	inline bool exist(std::vector<std::string> data, std::string key) const
	{
		for (int i = 0; i < data.size(); i++)
		{
			if (data.at(i).compare(key) == 0)
				return true;
		}
		return false;
	}

public:
	inline void addData(Entity ent)
	{
		this->table.push_back(ent);
	}

	inline void save(std::string path) noexcept
	{
		if (!path.size())
			return;

		std::ofstream nfile;
		nfile.open(path);

		// fetch header
		std::vector <std::string> header;
		for (int i = 0; i < table.size(); i++)
		{
			if (!exist(header, table.at(i).first))
				header.push_back(table.at(i).first);
		}

		// print header
		for (const auto &e : header)
		{
			nfile << e << ";";
		}
		nfile << "\n";

		// print data
		int headerPos = 0;
		int dataPos = 0;
		while(table.size() > 0)
		{
			if (table.at(dataPos).first.compare(header.at(headerPos)) == 0)
			{
				nfile << table.at(dataPos).second << ";";
				table.erase(table.begin() + dataPos);
				dataPos = 0; // reset after erase

				if (headerPos == header.size() - 1)
				{
					headerPos = 0;
					nfile << "\n";
				}
				else headerPos++;
			}
			else dataPos++;
		}

		nfile.close();
	}
};