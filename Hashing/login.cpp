//--------------------------------------------------------------------
//                         login.cpp
//
//  program that reads in username/login pairs and then
//  performs authentication of usernames.
//--------------------------------------------------------------------

#pragma warning( disable : 4290 )

#include "hashtbl.h"

#include <string>
#include <iostream>
#include <fstream>
using namespace std;

//This will be the data stored in the HashTbl (class T)
struct Password
{
  void setKey(string newKey) { username = newKey; }
  string getKey() const { return username; }

  //this hash converts a string to an integer
  int hash(const string str) const
  {
    int val = 0;

    for (unsigned int i = 0; i < str.length(); i++)
      val += str[i];
    return val;
  }
  string username,
    password;
};

int main()
{
  HashTbl<Password, string> passwords(10);
  Password tempPass;
  string name;      // user-supplied name
  string pass;      // user-supplied password
  //bool userFound;   // is user in table?

      //*********************************************************
      // Step 1: Read in the password file
      //*********************************************************
  ifstream passFile("password.txt");

  if (!passFile)
  {
    cout << "Unable to open 'password.txt'!" << endl;
    return 1;
  }
  passFile >> tempPass.username;
  while (!passFile.eof() && !passwords.isFull())
  {
    //**add line here to insert passwords into the HashTbl

    passFile >> tempPass.password;
  }

  cout << "Printing the hash table:..." << endl;
  //**add line here to show (print) the HashTbl


  //*********************************************************
  // Step 2: Prompt for a Login and Password and check if valid
  //*********************************************************
  cout << "Login: ";
  while (cin >> name)  // to quit, type CTRL Z in Visual C++
  {
    //**add line here to retrieve user from HashTbl


    cout << "Password: ";
    cin >> pass;

    //**add lines here to compare retrieved user password to
    //**input password and print "Authentication failure"
    //**or "Authentication successful"

    cout << "Login: ";
  }
  cout << endl;
}