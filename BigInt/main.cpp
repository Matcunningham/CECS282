// Mathew Cunningham
// CECS 282-05
// Prog 5 - BigInt
// 11/28/2017

#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

class BigInt
{
private:
	vector<int> storage;
	// I needed these next 2 functions but you may or may not need them depending how you implement your class
	void stripLeadingZero(BigInt &); // you need to make sure you don't have a number like this: '0123";
public:
	BigInt();
	BigInt(int);
	BigInt(string);
	BigInt operator++(int);
	bool operator<=(BigInt);
	bool operator==(int);
	bool operator==(BigInt);
	BigInt operator-(BigInt);
	BigInt operator-(int);
	BigInt operator+(BigInt);
	bool operator<(const BigInt &) const;  // this is required for the map
	friend ostream & operator<<(ostream &, const BigInt &);
};

// you must modify this function so that it runs in a reasonable time for input of 1000
// you must use a map<BigInt, BigInt>
BigInt GoldRabbits(BigInt bigN)
{
	static map<BigInt, BigInt> fiboMap;
	fiboMap[BigInt(0)] = BigInt(1);
	fiboMap[BigInt(1)] = BigInt(1);
	map<BigInt, BigInt>::iterator iter;
	if (bigN == 0 || bigN == 1)
	{
		return BigInt(1);
	}
	else
	{
		iter = fiboMap.find(bigN);
		if (iter != fiboMap.end())
		{
			return iter->second;
		}
		BigInt result = GoldRabbits(bigN - 1) + GoldRabbits(bigN - 2);
		fiboMap.insert(pair<BigInt, BigInt>(bigN, result));
		return result;
	}
}

// you must modify this function so it throws an exception if the result overflows
int fact(int n)
{
	if (n == 0)
	{
		return 1;
	}
	else
	{
		if (fact(n - 1) > 2147483647 / n)
		{
			throw "overflow exception";
		}
		return n * fact(n - 1);
	}
}


// here is the main function DO NOT CHANGE ANYTHING in this program.
int main()
{
	BigInt bigX(28675), bigY("46368"), bigResult;

	bigResult = bigX + bigY;
	cout << bigX << "+" << bigY << "=" << bigResult;
	getchar(); // pause

	for (BigInt n = 0; n <= 1000; n++)
	{
		cout << (n < 950 ? "\n" : "\n\n") << "The GoldRabbit of (" << n << ") is " << GoldRabbits(n);
		if (n == 30) // pause at 30
			getchar();
	}

	getchar(); // pause after GoldRabbits

	for (int i = 0; i<20; i++)
	{
		try {
			cout << "Fact(" << i << "):" << fact(i) << endl;
		}
		catch (...) {
			cout << "Fact(" << i << "):" << "Overflow" << endl;
		}
	}
	getchar();
}



BigInt::BigInt()
{
	storage.push_back(0);
}

void BigInt::stripLeadingZero(BigInt & bigN)
{
	while (bigN.storage.back() == 0 && bigN.storage.size() > 1)
	{
		bigN.storage.pop_back();
	}
}

BigInt::BigInt(int n)
{
	if (n == 0)
	{
		storage.push_back(0);
	}
	while (n != 0)
	{
		storage.push_back(n % 10);
		n = n / 10;
	}
}

BigInt::BigInt(string bigS)
{
	for (int i = bigS.size() - 1; i >= 0; i--)
	{
		storage.push_back(bigS.at(i) - '0');
	}
}

BigInt BigInt::operator++(int dumy)
{
	*this = *this + BigInt(1);
	return *this;
}

bool BigInt::operator<(const BigInt & bigN) const
{
	if (storage.size() < bigN.storage.size())
	{
		return true;
	}
	else if (storage.size() > bigN.storage.size())
	{
		return false;
	}
	else
	{
		for (int i = storage.size() - 1; i > 0; i--)
		{
			if (storage[i] < bigN.storage[i])
			{
				return true;
			}
			else if (storage[i] > bigN.storage[i])
			{
				return false;
			}
		}
		return storage < bigN.storage;
	}
}

bool BigInt::operator<=(BigInt bigN)
{
	if (*this == bigN || *this < bigN)
	{
		return true;
	}
	return false;
}

bool BigInt::operator==(BigInt bigN)
{
	if (storage.size() == bigN.storage.size())
	{
		for (int i = storage.size() - 1; i >= 0 && bigN.storage[i] == storage[i]; i--)
		{
			if (i == 0)
			{
				return true;
			}
		}
	}
	return false;
}

bool BigInt::operator==(int n)
{
	return *this == BigInt(n);
}

BigInt BigInt::operator-(int n)
{
	return *this - BigInt(n);
}

BigInt BigInt::operator-(BigInt bigN)
{
	BigInt temp;
	BigInt thisTemp(*this);
	temp.storage.pop_back();
	vector<int>::iterator thisIt = thisTemp.storage.begin();
	vector<int>::iterator bigNIt = bigN.storage.begin();
	int result;
	int borrowLoc = 0; // Borrow helper

	while (thisIt != thisTemp.storage.end() || bigNIt != bigN.storage.end())
	{
		if (bigNIt == bigN.storage.end())
		{
			result = *thisIt;
			temp.storage.push_back(result);
			thisIt++;
		}
		else
		{
			// borrow
			if (*thisIt - *bigNIt < 0)
			{
				*thisIt = *thisIt + 10; // Borrowed
				int finder = *thisIt;
				borrowLoc++;
				while (thisTemp.storage[borrowLoc] == 0) // Until reaches a value that can be borrowed from
				{
					borrowLoc++;
				}
				thisTemp.storage[borrowLoc] -= 1; // Borrows
				borrowLoc--;
				while (thisTemp.storage[borrowLoc] != finder) // If zero's between "borrower" and "borrowee",
				{											  // adds and borrows until the original number is found
					thisTemp.storage[borrowLoc] += 9;
					borrowLoc--;
				}
			}
			result = *thisIt - *bigNIt;
			temp.storage.push_back(result);
			thisIt++;
			bigNIt++;
		}
		borrowLoc++;
	}
	stripLeadingZero(temp);
	return temp;
}

BigInt BigInt::operator+(BigInt bigN)
{
	BigInt temp;
	temp.storage.pop_back();
	vector<int>::iterator thisIter = storage.begin();
	vector<int>::iterator bigNIter = bigN.storage.begin();
	int result;
	int carry = 0;

	while (thisIter != storage.end() || bigNIter != bigN.storage.end())
	{
		if (thisIter == storage.end())
		{
			result = *bigNIter + carry;
			if (result > 9)
			{
				carry = result / 10;
				result = result % 10;
			}
			else
			{
				carry = 0;
			}
			temp.storage.push_back(result);
			bigNIter++;
		}
		else if (bigNIter == bigN.storage.end())
		{
			result = *thisIter + carry;
			if (result > 9)
			{
				carry = result / 10;
				result = result % 10;
			}
			else
			{
				carry = 0;
			}
			temp.storage.push_back(result);
			thisIter++;
		}
		else
		{
			result = *thisIter + *bigNIter + carry;
			if (result > 9)
			{
				carry = result / 10;
				result = result % 10;
			}
			else
			{
				carry = 0;
			}
			temp.storage.push_back(result);
			thisIter++;
			bigNIter++;
		}
	}
	if (carry != 0)
	{
		temp.storage.push_back(carry);
	}
	return temp;
}

ostream & operator<<(ostream & out, const BigInt & bigN)
{
	vector<int>::const_reverse_iterator rit;
	for (rit = bigN.storage.rbegin(); rit != bigN.storage.rend(); rit++)
	{
		out << *rit;
	}
	return out;
}