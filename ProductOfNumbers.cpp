//
//
// Task :  It is required to find the smallest natural number Q such that the product of its digits is equal to the given number N.
//
//
#include <iostream>
#include <fstream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

bool isPrime(long long  number);
size_t decompose(long long  number);
size_t findTheSmallestNumber(int *&digitArray, int arraySize);

int main()
{
	long long givenNumber = 0;

	std::ifstream inputFile;
	inputFile.open("input.txt", std::ios::out);

	if (inputFile.is_open())
	{
		inputFile >> givenNumber;
		
		givenNumber = abs(givenNumber);

		inputFile.close();
	}
	else
	{
		cout << "Problems with reading file...\n";

		return 0;
	}

	std::ofstream outputFile;
	outputFile.open("output.txt", std::ios::in | std::ios::app);

	if (outputFile.is_open())
	{
		if (givenNumber == 0)
		{
			outputFile << "0 \n----------------\n";
		}
		else if (isPrime(givenNumber))
		{
			outputFile << "-1 \n----------------\n";
		}
		else
		{
			outputFile << std::to_string(static_cast<int>(decompose(givenNumber))) << "\n----------------\n";
		}

		inputFile.close();
	}
	else
	{
		cout << "Problems with writing in file....\n";
	}

	return 0;
}

bool isPrime(long long number)
{
	if (number <= 3) return number > 1;
	else if (number % 2 == 0 || number % 3 == 0) return false;
	else
	{
		for (long long i = 5; i * i <= number; i += 6)
		{
			if (number % i == 0 || number % (i + 2) == 0) return false;
		}

		return true;
	}
}

size_t decompose(long long  number)
{
	long long  tempNumber = number;
	int multipliersCounter = 0;
	int multiplier = 2;

	string multipliersSequence = "";

	do
	{
		if (tempNumber % multiplier == 0)
		{
			multipliersCounter++;
			tempNumber /= multiplier;

			multipliersSequence += std::to_string(multiplier);

			if(tempNumber > 10) if (isPrime(tempNumber)) return -1;
		}
		else
		{
			multiplier++;
		}

	} while (tempNumber > 1);

	int* multipliersArray = new int[multipliersCounter]();

	for (int i = 0; i < multipliersCounter; i++)
	{	
		multipliersArray[i] = multipliersSequence[i] - 48;

	}

	return findTheSmallestNumber(multipliersArray, multipliersCounter);
}

size_t findTheSmallestNumber(int *&digitArray, int arraySize)
{
	string resultSequence = "";
	
	size_t tempValue = 0;
	int index = 0;

	while (true)
	{
		if (index >= arraySize) break;

		tempValue = digitArray[index];

		while ((index < arraySize - 1) && (tempValue * digitArray[index + 1] < 10))
		{
			tempValue *= digitArray[index + 1];
			
			index++;
		}

		resultSequence += std::to_string(tempValue);

		index++;
	}

	//--deleting dynamic array--

	delete[] digitArray;

	//--re-declar dynamic array--

	size_t* newDigitArray = new size_t[resultSequence.size()]();
	
	for (size_t i = 0; i < resultSequence.size(); i++)
	{
		newDigitArray[i] = resultSequence[i] - 48;
	}

	//--Shella`s sorting algorithm--

	size_t step = resultSequence.length() / 2;

	while (step > 0)
	{
		for (size_t i = step; i < resultSequence.length(); i++)
		{
			size_t temp = newDigitArray[i];

			size_t j;

			for (j = i; j >= step && newDigitArray[j - step] > temp; j -= step)
			{
				newDigitArray[j] = newDigitArray[j - step];
			}

			newDigitArray[j] = temp;
		}

		step /= 2;
	}

	//--translating into a number--
	
	size_t resultNumber = 0;

	for (size_t i = 0; i < resultSequence.size(); i++)
	{
		resultNumber += static_cast<size_t>(newDigitArray[i] * pow(10, resultSequence.size() - i - 1));
	}

	//--deleting dynamic array--

	delete[] newDigitArray;

	return resultNumber;
}