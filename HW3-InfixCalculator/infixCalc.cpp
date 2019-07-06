#include "llStack.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <climits>
using namespace std;
const int MAX_ARRAY_SIZE = 99;
void add(LLStack<int>& stack);
void subtract(LLStack<int>& stack);
void multiply(LLStack<int>& stack);
void divide(LLStack<int>& stack);
void processInput(string stringInput[], int count);
void errorCheck(int size);

int main(int argc, char* argv[])
{
	cout << "Chris Kelley's Postfix Calculator of Wonder!";
	cout << endl << endl;
	string fileName;
	ifstream inFile;
	char answer;
    
    //get file information
	if (argc > 1)
	{
		fileName = argv[1];
		inFile.open(fileName);
	}
	else
	{
		cout << "Would you like to Read from a file?" << endl;
		cout << "(Y/y for yes, any other key for console input)" << endl;
		cin >> answer;
		//clear buffer
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		if (answer == 'y' || answer == 'Y')
		{
			cout << "Enter the name of the file: " << endl;
			cin >> fileName;
			inFile.open(fileName);
		}
	}
    
    //read in file or console data
	if (argc > 1 || (answer == 'y' || answer == 'Y'))
	{
        //failure to open file
		if (!inFile)
		{
			cout << "ERROR: Unable to Open File" << endl;
			cout << "Better luck next time." << endl;
			cout << "Bye!!" << endl;
			return 1;
		}
        //read in data from file
		cout << "Reading from: " << fileName << endl << endl;
		string stream;
		string inputString[MAX_ARRAY_SIZE];
		int count = 0;
		while (inFile >> stream)
		{
			inputString[count] = stream;
			count++;
		}
		inFile.close();
		processInput(inputString, count);

	}
    //if no file data, read input from console
	else
	{
		cout << "Enter some numbers for the time of your life: " << endl;
		string inputString[MAX_ARRAY_SIZE];
		int count = 0;
		string stream;
		string newString;


		getline(cin, newString);
		stringstream ss(newString);

		while (ss >> stream)
		{
			inputString[count] = stream;
			count++;
		}

		processInput(inputString, count);
	}
}

//take string array parameter with input data
//and calculate output.
//If data is a number, put on a stack
//If data is a operator symbol, apply to first
//two numbers on the number stack.
void processInput(string stringInput[], int count)
{
	LLStack<int> stack;
	int x = 0;

    //identify whether input item is a symbol or
    //a number. If symbol, send to designated 
    //method to calculate.
	for (int i = 0; i < count; i++)
	{
		if (stringInput[i].compare("+") == 0)
		{
			add(stack);
		}
		else if (stringInput[i].compare("-") == 0)
		{
			subtract(stack);
		}

		else if (stringInput[i].compare("*") == 0)
		{
			multiply(stack);
		}
		else if (stringInput[i].compare("/") == 0)
		{
			divide(stack);
		}
		else
		{
			x = stoi(stringInput[i], nullptr, 0);
			stack.push(x);
		}
	}

    //invalid information provided: to many or to few
    //numbers provided in input
	if(stack.size() != 1)
	{
		cout << "ERROR: Invalid Information Provided" << endl;
	}
	else
	{
		cout << "ANSWER: ";
		cout << stack.top() << endl;
	}
}

//add first two numbers on number stack
void add(LLStack<int>& stack)
{
	errorCheck(stack.size());
	int num1 = stack.top();
	stack.pop();
	int num2 = stack.top();
	stack.pop();
	stack.push(num1 + num2);
}

//subtract first number on stack from
//second number on stack
void subtract(LLStack<int>& stack)
{
	errorCheck(stack.size());
	int num1 = stack.top();
	stack.pop();
	int num2 = stack.top();
	stack.pop();
	stack.push(num2 - num1);
}

//multiply first two items on the stack
void multiply(LLStack<int>& stack)
{
	errorCheck(stack.size());
	int num1 = stack.top();
	stack.pop();
	int num2 = stack.top();
	stack.pop();
	stack.push(num1 * num2);
}

//divide second item on the stack by
//the first number on the stack
void divide(LLStack<int>& stack)
{
	errorCheck(stack.size());
	int num1 = stack.top();
	stack.pop();
	int num2 = stack.top();
	stack.pop();
	stack.push(num2 / num1);
}

//Check if operation(+,-,*,/) can be performed on
//first two numbers on the stack
void errorCheck(int size)
{
	if(size < 2)
	{
		cout << "ERROR: Invalid Information Provided";
		exit(EXIT_FAILURE);
	}
}
