#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include "Book.h"
using namespace std;

void SetScreenGrid();
void SetSysCaption();
void ClearScreen();
void ShowWelcome();
void ShowRootMenu();
void WaitUser();
void WaitView(int);
void mainloop();
int GetSelect();
void GuideInput();
void ViewData(int iSelPage = 1);
long GetFileLength(ifstream &);
void DeleteBookFromFile();

void SetScreenGrid() {
  cout << "Sorry! It's not compile." << endl;
}

void SetSysCaption() {
  cout << "Sorry! title setting is not compile." << endl;
}

void ClearScreen() {
  system("clear");
}

void ShowWelcome() {
  for (int i=-0; i<7; i++) {
    cout <<endl;
  }
  cout << setw(40);
  cout << "**********" << endl;
  cout << setw(40);
  cout << "Book Manage System" << endl;
  cout << setw(40);
  cout << "**********" << endl;
}

void ShowRootMenu() {
  cout << setw(40);
  cout << "Please select: " << endl;
  cout << endl;
  cout << setw(38);
  cout << "1. Add new book" << endl;
  cout << endl;
  cout << setw(38);
  cout << "2. See all" << endl;
  cout << endl;
  cout << setw(38);
  cout << "3. Delete book" << endl;
}

void WaitUser() {
  int iInputPage = 0;
  cout << "enter(Menu) q(quit)" << endl;
  char buf[256];
  gets(buf);
  if (buf[0] == 'q')
    system("exit");
}

void mainloop() {
  ShowWelcome();
  while (1) {
    ClearScreen();
    ShowWelcome();
    ShowRootMenu();
    switch(GetSelect()) {
      case 1:
        ClearScreen();
        GuideInput();
        break;
      case 2:
        ClearScreen();
        ViewData();
        break;
      case 3:
        ClearScreen();
        DeleteBookFromFile();
        break;
    }
  }
}

int GetSelect() {
  char buf[256];
  gets(buf);
  return atoi(buf);
}

void GuideInput() {
  char inName[NUM1];
  char inIsbn[NUM1];
  char inPrice[NUM2];
  char inAuthor[NUM2];
  cout << "Enter the name of book:" << endl;
  cin >> inName;
  cout << "Enter the ISBN of book:" << endl;
  cin >> inIsbn;
  cout << "Enter the price of book:" << endl;
  cin >> inPrice;
  cout << "Enter the author of book:" << endl;
  cin >> inAuthor;
  CBook book(inName, inIsbn, inPrice, inAuthor);
  book.WriteData();
  cout << "Write Finish" << endl;
  WaitUser();
}

void WaitView(int iCurPage) {
  char buf[256];
  gets(buf);
  if (buf[0] == 'q')
    system("exit");
  if (buf[0] == 'm')
    mainloop();
  if (buf[0] == 'n')
     ViewData(iCurPage);
}

void ViewData(int iSelPage) {
  int iPage = 0;
  int iCurPage = 0;
  int iDataCount = 0;
  char inName[NUM1];
  char inIsbn[NUM1];
  char price[NUM2];
  char inAuthor[NUM2];
  bool bIndex = false;
  int iFileLength;
  iCurPage = iSelPage;
  ifstream ifile;
  ifile.open("book.dat", ios::binary);
  iFileLength = GetFileLength(ifile);
  iDataCount = iFileLength/(NUM1*2 + NUM2*2);
  if (iDataCount >= 1)
    bIndex = true;
  iPage = iDataCount / 20 + 1;
  ClearScreen();
  cout << " total record" << iDataCount << " ";
  cout << " total pages" << iPage << " ";
  cout << " now page" << iCurPage << " ";
  cout << " n view next m back" << endl;
  cout << setw(5) << "index";
  cout << setw(22) << "Name" << setw(22) << "Isbn";
  cout << setw(15) << "Price" << setw(15) << "Author";
  cout << endl;
  try {
    ifile.seekg((iCurPage-1)*20*(NUM1*2+NUM2*2), ios::beg);
    if (!ifile.fail()) {
      for (int i=1; i<21; i++) {
        memset(inName, 0, 128);
        memset(inIsbn, 0, 128);
        memset(price, 0, 50);
        memset(inAuthor, 0, 50);
        if (bIndex)
          cout << setw(3) << ((iCurPage-1)*20+i);
        ifile.read(inName, NUM1);
        cout << setw(24) << inName;
        ifile.read(inIsbn, NUM1);
        cout << setw(24) << inIsbn;
        ifile.read(price, NUM2);
        cout << setw(12) << price;
        ifile.read(inAuthor, NUM2);
        cout << setw(12) << inAuthor;
        cout << endl;
        if (ifile.tellg() < 0)
          bIndex = false;
        else
          bIndex = true;
      }
    }
  }
  catch(...) {
    cout << "throw file exception" << endl;
    throw "file error occurred";
    ifile.close();
  }
  if (iCurPage < iPage) {
    iCurPage = iCurPage + 1;
    WaitView(iCurPage);
  }
  else {
    WaitView(iCurPage);
  }
  ifile.close();
}

long GetFileLength(ifstream & ifs) {
  long tmppos;
  long respos;
  tmppos = ifs.tellg();
  ifs.seekg(0, ios::end);
  respos = ifs.tellg();
  ifs.seekg(tmppos, ios::beg);
  return respos;
}

void DeleteBookFromFile() {
  int iDelCount;
  cout << "Input delete index" << endl;
  cin >> iDelCount;
  CBook tmpbook;
  tmpbook.DeleteData(iDelCount);
  cout << "Delete Finish" << endl;
  WaitUser();
}

int main() {
  SetScreenGrid();
  SetSysCaption();
  mainloop();
}
