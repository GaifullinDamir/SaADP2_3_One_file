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
	ShowMenu, SimpleFeedSort, FeedSort, GeneralFeedSort, Exit,
	LineWidth = 20
};

/*   LIST   */
void addItem(ListItem*& pHead, int data)
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

void clearMemoryList(ListItem* currentArray[], int size)
{
	ListItem* pCurrent ;
	for (int i = 0; i < size; i++)
	{
		pCurrent = currentArray[i]->next;
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

void showArrayOfList(ListItem* currentArray[], int size)
{
	ListItem* pCurrent; int steps;
	for (int i = 0; i < size; i++)
	{
		steps = 1;
		pCurrent = currentArray[i]->next;
		while (pCurrent != nullptr)
		{
			if (steps % LineWidth == 0) { cout << "\n"; }
			cout << pCurrent->data << "   ";
			pCurrent = pCurrent->next;
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

void generalFeedSort(ListItem* auxArray[], Array* currentArray, int& countExchanges, int size)
{	
	for (int i = 0; i < size; i++)
	{
		addItem(auxArray[currentArray[i].key], currentArray[i].key);
		countExchanges++;
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
	int value = 0;
	while (value < minValue || value > maxValue) { cout << "   Enter: "; value = input(); }
	return value;
}

void printMenu()
{
	cout << endl;
	cout
		<< "\n1. Simple feed sort."
		<< "\n2. Feed sort."
		<< "\n4. Exit." << endl;
}

void showInfo(Array* mainArray, Array* auxArray, int countCompares, int countExchanges, int size)
{
	cout << "\n   Before sorting:\n   ";
	show(mainArray, size);
	cout << "\n\n   After sorting:\n   ";
	show(auxArray, size);
	cout << "\n   Number of comparisons: " << countCompares << "\n\n   Number of exchanges: " << countExchanges << "\n\n";
}

void showInfoGeneralFeed(Array* mainArray, ListItem* auxArray, int countCompares, int countExchanges, int size)
{
	cout << "\n   Before sorting:\n   ";
	show(mainArray, size);
	cout << "\n\n   After sorting:\n   ";
	showArrayOfList(&auxArray, size);
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

	ListItem* auxArray = new ListItem[MaxKey];
	for (int cell = 0; cell < maxKey; cell++)
	{
		auxArray[cell].next = nullptr;
	}
	generalFeedSort(&auxArray, mainArray, countExchanges, size);
	showInfoGeneralFeed(mainArray, auxArray, countCompares, countExchanges, size);
	clearMemory(mainArray, size);
	clearMemoryList(&auxArray, maxKey);
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