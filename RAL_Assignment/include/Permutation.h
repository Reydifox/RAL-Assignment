#pragma once
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>

#define FILE_PATH "sequences.txt"

using StringArray = std::vector<std::string>;

namespace Permutation
{
	inline void parseStringToArray(std::string &arr, StringArray &buf)
	{
		std::ofstream nfile;
		nfile.open(FILE_PATH);
		for (const auto s : arr)
		{
			nfile << s;
		}
		nfile.close();

		std::string line;
		std::ifstream ofile(FILE_PATH);
		if (ofile.is_open())
		{
			while (getline(ofile, line))
			{
				buf.push_back(line);
			}
			ofile.close();
		}
	}

	inline void generateStringSequence(int n, int field, std::string &buff, bool verbose = false)
	{
		std::string tmp;
		for (int i = 0; i < field; i++)
			tmp.append(std::to_string(i));

		const char* alphabet = tmp.c_str();

		int   alphaLen = strlen(alphabet);
		int   len = 0;
		char* buffer = (char*)malloc((n + 1) * alphaLen * alphaLen);
		int* letters = (int*)malloc(n * sizeof(int));

		// This for loop generates all 1 letter patterns, then 2 letters, etc,
		// up to the given maxlen.
		for (len = n; len <= n; len++) {
			// The stride is one larger than len because each line has a '\n'.
			int i;
			int stride = len + 1;
			int bufLen = stride * alphaLen * alphaLen;

			if (len == 1) {
				// Special case.  The main algorithm hardcodes the last two
				// letters, so this case needs to be handled separately.
				int j = 0;
				bufLen = (len + 1) * alphaLen;
				for (i = 0; i < alphaLen; i++) {
					buffer[j++] = alphabet[i];
					buffer[j++] = '\n';
				}
				for (int x = 0; x < bufLen; x++) {
					if(verbose) 
						printf("%c", buffer[x]);
					buff.push_back(buffer[x]);
				}
				continue;
			}

			// Initialize buffer to contain all first letters.
			memset(buffer, alphabet[0], bufLen);

			// Now in buffer, write all the last 2 letters and newlines, which
			// will after this not change during the main algorithm.
			{
				// Let0 is the 2nd to last letter.  Let1 is the last letter.
				int let0 = 0;
				int let1 = 0;
				for (i = len - 2; i < bufLen; i += stride) {
					buffer[i] = alphabet[let0];
					buffer[i + 1] = alphabet[let1++];
					buffer[i + 2] = '\n';
					if (let1 == alphaLen) {
						let1 = 0;
						let0++;
						if (let0 == alphaLen)
							let0 = 0;
					}
				}
			}

			// Write the first sequence out.
			for (int x = 0; x < bufLen; x++) {
				if (verbose)
					printf("%c", buffer[x]);
				buff.push_back(buffer[x]);
			}

			// Special case for length 2, we're already done.
			if (len == 2)
				continue;

			// Set all the letters to 0.
			for (i = 0; i < len; i++)
				letters[i] = 0;

			// Now on each iteration, increment the the third to last letter.
			i = len - 3;
			do {
				char c;
				int  j;

				// Increment this letter.
				letters[i]++;

				// Handle wraparound.
				if (letters[i] >= alphaLen)
					letters[i] = 0;

				// Set this letter in the proper places in the buffer.
				c = alphabet[letters[i]];
				for (j = i; j < bufLen; j += stride)
					buffer[j] = c;

				if (letters[i] != 0) {
					// No wraparound, so we finally finished incrementing.
					// Write out this set.  Reset i back to third to last letter.
					for (int x = 0; x < bufLen - 1; x++) {
						if (buffer[x] - 48 == -38)
						{
							buff.push_back('\n');
							if (verbose)
								printf("\n");
						}
						else
						{
							buff.push_back(buffer[x]);
							if (verbose)
								printf("%c", buffer[x]);
						}
					}
					buff.push_back('\n');
					if (verbose)
						printf("\n");

					i = len - 3;
					continue;
				}

				// The letter wrapped around ("carried").  Set up to increment
				// the next letter on the left.
				i--;
				// If we carried past last letter, we're done with this
				// whole length.
				if (i < 0)
					break;
			} while (1);
		}

		// Clean up.
		free(letters);
		free(buffer);
	}
}