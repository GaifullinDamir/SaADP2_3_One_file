#include <iostream>
#include <string>

using namespace std;

struct Array
{
	int key;
};
enum sorting 
{
	MinNumber = 0, MaxNumber = 250,
	MinSize = 1, MaxSize = 10000
};
enum userInterface 
{ 
	ShowMenu, SimpleFeedSort, FeedSort, Exit,
	LineWidth = 20
};

/*   SORTING   METHODS   */

int random(int max) { return MinNumber + rand() % (max - MinNumber + 1); }

void fillSortedArray(Array* currentArray, int size)
{
	for (int cell = 0; cell < size; cell++) { currentArray[cell].key = cell;	}
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

int sizeInput()
{
	int size = 0;
	while (size < MinSize || size > MaxSize) { cout << "   Enter the size (1 - 10000): "; size = input(); }
	return size;
}

void printMenu()
{
	cout << endl;
	cout
		<< "\n1. Simple feed sort."
		<< "\n2. Feed sort."
		<< "\n4. Exit." << endl;
}

void showInfo(Array* mainArray, Array* auxArray, int& countCompares, int& countExchanges, int size)
{
	cout << "\n   Before sorting:\n   ";
	show(mainArray, size);
	cout << "\n\n   After sorting:\n   ";
	show(auxArray, size);
	cout << "\n   Number of comparisons: " << countCompares << "\n\n   Number of exchanges: " << countExchanges << "\n\n";
}

void caseSimpleFeedSort(int size)
{
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

void caseFeedSort(int size)
{
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

void userInterface()
{
	int size = sizeInput();
	bool stop = false; printMenu();

	while (!stop)
	{
		cout << "   Choice: ";
		switch (input())
		{
		case ShowMenu:       { printMenu(); break; }
		case SimpleFeedSort: { caseSimpleFeedSort(size); break; }
		case FeedSort:       { caseFeedSort(size); break; }
		case Exit:           { stop = true; break; }
		default:               cout << "   There is no such menu item.\n\n"; break;
		}
		cout << "   (0) - show menu.\n";
	}
}


int main()
{
	userInterface();
}