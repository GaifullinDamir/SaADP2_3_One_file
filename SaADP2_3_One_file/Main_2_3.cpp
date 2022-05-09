#include <iostream>
#include <string>

using namespace std;

struct Array
{
	int key;
};

struct ListItem
{
	int data;
	ListItem* next;
};

enum sorting
{
	MinNumber = 0, MaxNumber = 250,
	MinSize = 1, MaxSize = 10000, MinKey = 0, MaxKey = 9999
};
enum userInterface
{
	ShowMenu, SimpleFeedSort, FeedSort, GeneralFeedSort, RadixSort, Exit,
	LineWidth = 20
};

/*   LIST   */
void addItem(ListItem* pHead, int data)
{
	ListItem* pCurrent = pHead;
	while (pCurrent->next != nullptr)
	{
		pCurrent = pCurrent->next;
	}
	pCurrent->next = new ListItem;
	pCurrent->next->data = data;
	pCurrent->next->next = nullptr;
}

void clearMemoryList(ListItem* currentArray, int size)
{
	ListItem* pCurrent ;
	for (int i = 0; i < size; i++)
	{
		pCurrent = currentArray[i].next;
		while (pCurrent != nullptr)
		{
			ListItem* pTemp = pCurrent;
			pCurrent = pCurrent->next;
			delete pTemp;
		}
		pCurrent = nullptr;
	}
	delete[] currentArray; currentArray = nullptr;
}

void showArrayOfList(ListItem* currentArray, int size)
{
	ListItem* pCurrent; int steps = 0;
	for (int i = 0; i < size; i++)
	{
		pCurrent = currentArray[i].next;
		while (pCurrent != nullptr)
		{
			if (steps % LineWidth == 0) 
			{
				cout << "\n";
			}
			cout << pCurrent->data << " ";
			pCurrent = pCurrent->next;
			steps++;
		}
	}
}
/*   SORTING   METHODS   */

int random(int max) { return MinNumber + rand() % (max - MinNumber + 1); }

void fillRandomArray(Array* currentArray, int size, int maxKey)
{
	for (int cell = 0; cell < size; cell++)
	{
		currentArray[cell].key = random(maxKey);
	}
}

void fillDigitRandom(Array* currentArray, int size, int maxDigit)
{
	int maxNumb;
	if (maxDigit == 1) { maxNumb = 9; }
	else if (maxDigit == 2) { maxNumb = 99; }
	else if (maxDigit == 3) { maxNumb = 999; }
	else maxNumb = 9999; 
	for (int cell = 0; cell < size; cell++)
	{
		currentArray[cell].key = random(maxNumb);
	}
}
void fillSortedArray(Array* currentArray, int size)
{
	for (int cell = 0; cell < size; cell++) 
	{ 
		currentArray[cell].key = cell;	
	}
}

void shuffleArray(Array* currentArray, int size)
{
	Array temporary;
	for (int i = 0; i < size; i++)
	{
		int index = random(size - 1);
		temporary = currentArray[index];
		currentArray[index] = currentArray[i];
		currentArray[i] = temporary;
	}
}

void duplicateArray(Array* mainArray, Array* auxArray, int size)
{ 
	for (int cell = 0; cell < size; cell++) { auxArray[cell] = mainArray[cell]; }
}

void show(Array* currentArray, int size)
{
	for (int cell = 0; cell < size; cell++)
	{
		if (cell % LineWidth == 0) { cout << "\n"; }
		cout << currentArray[cell].key << " ";
	}
}

void clearMemory(Array* currentArray, int size)
{
	delete[] currentArray;
	currentArray = nullptr;
}

void simpleFeedSort(Array* currentArray, int& countCompares, int& countExchanges, int size)
{
	Array temp; int tempKey;
	for (int cell = 0; cell < size; cell++)
	{
		while (currentArray[cell].key != cell)
		{
			countCompares++;
			temp = currentArray[cell];
			tempKey = currentArray[cell].key;
			currentArray[cell] = currentArray[currentArray[cell].key];
			currentArray[tempKey] = temp;
			countExchanges++;
		}
		countCompares++;
	}
}

void feedSort(Array* mainArray, Array* auxArray, int& countExchanges, int size)
{
	for (int i = 0; i < size; i++)
	{
		auxArray[mainArray[i].key] = mainArray[i];
		countExchanges++;
	}
}

void generalFeedSort(ListItem* auxArray, Array* currentArray, int& countExchanges, int size)
{	
	for (int i = 0; i < size; i++)
	{
		addItem(&auxArray[currentArray[i].key], currentArray[i].key);
		countExchanges++;
	}
}

void radixSort(Array* currentArray, int& countExchanges, int k, int size)
{
	ListItem* radix = new ListItem[10];
	ListItem* pCurrent;

	int tempKey;

	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			radix[j].next = nullptr;
		}
		for (int m = 0; m < size; m++)
		{
			if (i == 0)
			{
				tempKey = currentArray[m].key % 10;
			}
			else if (i == 1)
			{
				tempKey = currentArray[m].key % 100 / 10;
			}
			else if (i == 2)
			{
				tempKey = currentArray[m].key % 1000 / 100;
			}
			else if (i == 3)
			{
				tempKey = currentArray[m].key % 10000 / 1000;
			}
			addItem(&radix[tempKey], currentArray[m].key);
			countExchanges++;
		}
		int steps = 0;
		for (int r = 0; r < 10; r++)
		{
			pCurrent = radix[r].next;
			while (pCurrent != nullptr)
			{
				currentArray[steps].key = pCurrent->data;
				pCurrent = pCurrent->next;
				steps++;
			}
		}
	}
}
/*   INTERFACE METHODS   */

int input()
{
	int number = 0; bool check = true; string numberInput;
	while (check)
	{
		try { cin >> numberInput; number = stoi(numberInput); check = false; }
		catch (const std::exception&) { cout << "   Wrong input.\n\n"; check = true; }
	}
	return number;
}

int sizeInput(int minValue, int maxValue)
{
	int value = -1;
	while (value < minValue || value > maxValue) { cout << "   Enter: "; value = input(); }
	return value;
}

void printMenu()
{
	cout << endl;
	cout
		<< "\n1. Simple feed sort."
		<< "\n2. Feed sort."
		<< "\n3. General feed sort."
		<< "\n4. Radix sort."
		<< "\n5. Exit." << endl;
}

void showInfo(Array* mainArray, Array* auxArray, int countCompares, int countExchanges, int size)
{
	cout << "\n   Before sorting:\n   ";
	show(mainArray, size);
	cout << "\n\n   After sorting:\n   ";
	show(auxArray, size);
	cout << "\n   Number of comparisons: " << countCompares << "\n\n   Number of exchanges: " << countExchanges << "\n\n";
}

void showInfoGeneralFeed(Array* mainArray, ListItem* auxArray, int countCompares, int countExchanges, int size, int maxKey)
{
	cout << "\n   Before sorting:\n   ";
	show(mainArray, size);
	cout << "\n\n   After sorting:\n   ";
	showArrayOfList(auxArray, maxKey + 1);
	cout << "\n   Number of comparisons: " << countCompares << "\n\n   Number of exchanges: " << countExchanges << "\n\n";
}

void caseSimpleFeedSort()
{
	cout << "   Enter the maximum array size (> 0, < 10 000)\n"; int size = sizeInput(MinSize, MaxSize);
	int countCompares{ 0 }, countExchanges{ 0 };
	Array* mainArray = new Array[size];
	Array* auxArray = new Array[size];
	fillSortedArray(mainArray, size);
	shuffleArray(mainArray, size);
	duplicateArray(mainArray, auxArray, size);
	simpleFeedSort(auxArray, countCompares, countExchanges, size);
	showInfo(mainArray, auxArray, countCompares, countExchanges, size);
	clearMemory(mainArray, size);
	clearMemory(auxArray, size);
}

void caseFeedSort()
{
	cout << "   Enter the maximum array size (> 0, < 10 000)\n"; int size = sizeInput(MinSize, MaxSize);
	int countCompares{ 0 }, countExchanges{ 0 };
	Array* mainArray = new Array[size];
	Array* auxArray = new Array[size];
	fillSortedArray(mainArray, size);
	shuffleArray(mainArray, size);
	feedSort(mainArray, auxArray, countExchanges, size);
	showInfo(mainArray, auxArray, countCompares, countExchanges, size);
	clearMemory(mainArray, size);
	clearMemory(auxArray, size);
}

void caseGeneralFeedSort()
{
	cout << "   Enter the maximum key value (> 0, < 9 999)\n"; int maxKey = sizeInput(MinKey, MaxKey);
	cout << "   Enter the maximum array size (> maxKey, < 10 000)\n"; int size = sizeInput(maxKey, MaxSize);
	int countCompares{ 0 }, countExchanges{ 0 };
	Array* mainArray = new Array[size];
	fillRandomArray(mainArray, size, maxKey);

	ListItem* auxArray = new ListItem[maxKey + 1];
	for (int cell = 0; cell < maxKey + 1; cell++)
	{
		auxArray[cell].next = nullptr;
	}
	generalFeedSort(auxArray, mainArray, countExchanges, size);
	showInfoGeneralFeed(mainArray, auxArray, countCompares, countExchanges, size, maxKey);
	clearMemory(mainArray, size);
	clearMemoryList(auxArray, maxKey );
}

void caseRadixSort()
{
	cout << "   Enter the maximum array size (> 0, < 10 000)\n"; int size = sizeInput(MinSize, MaxSize);
	cout << "   Enter the maximum digit of the number (1 - 4)\n"; int digit = sizeInput(1, 4);

	int countCompares{ 0 }, countExchanges{ 0 };
	Array* mainArray = new Array[size];
	fillDigitRandom(mainArray, size, digit);
	Array* auxArray = new Array[size];
	duplicateArray(mainArray, auxArray, size);
	radixSort(auxArray, countExchanges, digit, size);
	showInfo(mainArray, auxArray, countCompares, countExchanges, size);
	clearMemory(mainArray, size);
	clearMemory(auxArray, size);
}

void userInterface()
{
	bool stop = false; printMenu();

	while (!stop)
	{
		cout << "   Choice: ";
		switch (input())
		{
		case ShowMenu:        { printMenu(); break; }
		case SimpleFeedSort:  { caseSimpleFeedSort(); break; }
		case FeedSort:        { caseFeedSort(); break; }
		case GeneralFeedSort: { caseGeneralFeedSort(); break; }
		case RadixSort:       { caseRadixSort(); break; }
		case Exit:            { stop = true; break; }
		default:                cout << "   There is no such menu item.\n\n"; break;
		}
		cout << "   (0) - show menu.\n";
	}
}


int main()
{
	userInterface();
}