#pragma once
#include <string>
#include <map>

using namespace std;

/*
 *  Grocery Frequency Program
 *
 *  Main.h
 *
 *  Date: 12-9-2022
 *  Author: Liam Rand
 */


#ifndef GROCER_MAIN_H_
#define GROCER_MAIN_H_

void PrintTitle();
void PrintMenu();
void PrintHeader(string titleName);
int GetNumberInput(string message = "Input >", int minInput = -1, int maxInput = -1);
string GetStringInput(string message);
void WaitForContinue();
map<string, int> ReadFrequencyData();
void CreateHistogram(map<string, int>& groceryList, char histogramChar);


HANDLE hConsole;
bool runProgram = true;
static string GROCERY_FILE = "CS210_Project_Three_Input_File.txt";
static string ITEM_FREQUENCY_FILE = "frequency.dat";

#endif // GROCER_MAIN_H_
