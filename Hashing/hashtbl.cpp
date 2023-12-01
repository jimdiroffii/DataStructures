//--------------------------------------------------------------------
//                        hashtbl.cpp
//--------------------------------------------------------------------
#pragma warning( disable : 4290 )

#include "hashtbl.h"
#include "listlnk.h"

#include <exception>
#include <iostream>
using namespace std;

template < class T, class KF >
HashTbl<T, KF>::HashTbl(int initTableSize) : tableSize(initTableSize)
{
  dataTable = new List<T>[tableSize];
}

template < class T, class KF >
HashTbl<T, KF>:: ~HashTbl()
{
  delete[] dataTable;
}

template < class T, class KF >
void HashTbl<T, KF>::insert(const T& newDataItem) throw (bad_alloc)
{
  int index = 0;
  index = newDataItem.hash(newDataItem.getKey()) % tableSize;

  if (dataTable[index].isEmpty())
    dataTable[index].insert(newDataItem);
  else
  {
    dataTable[index].gotoBeginning();
    do
    {
      if (dataTable[index].getCursor().getKey() == newDataItem.getKey())
      {
        dataTable[index].replace(newDataItem);
        return;
      }
    } while (dataTable[index].gotoNext());

    dataTable[index].insert(newDataItem);
  }
}

template < class T, class KF >
bool HashTbl<T, KF>::remove(KF searchKey)
{
  T temp{};
  int index = 0;
  index = temp.hash(searchKey) % tableSize;

  if (dataTable[index].isEmpty())
    return false;

  dataTable[index].gotoBeginning();
  do
  {
    if (dataTable[index].getCursor().getKey() == searchKey)
    {
      dataTable[index].remove();
      return true;
    }
  } while (dataTable[index].gotoNext());

  return false;
}

template < class T, class KF >
bool HashTbl<T, KF>::retrieve(KF searchKey, T& dataItem)
{
  // apply two hash functions:
  // convert string (searchkey) to integer
  // and use the remainder method (% tableSize) to get the index

  int index = 0;
  index = dataItem.hash(searchKey) % tableSize;

  if (dataTable[index].isEmpty())
    return false;

  dataTable[index].gotoBeginning();
  do
  {
    if (dataTable[index].getCursor().getKey() == searchKey)
    {
      dataItem = dataTable[index].getCursor();
      return true;
    }
  } while (dataTable[index].gotoNext());

  return false;
}

template < class T, class KF >
void HashTbl<T, KF>::clear()
{
  for (int i = 0; i < tableSize; i++)
  {
    dataTable[i].clear();
  }
}

template < class T, class KF >
bool HashTbl<T, KF>::isEmpty() const
{
  for (int i = 0; i < tableSize; i++)
  {
    if (!dataTable[i].isEmpty())
      return false;
  }

  return true;
}

template < class T, class KF >
bool HashTbl<T, KF>::isFull() const
{
  for (int i = 0; i < tableSize; i++)
  {
    if (!dataTable[i].isFull())
      return false;
  }

  return true;
}

template < class T, class KF >
void HashTbl<T, KF>::showStructure() const
{
  cout << "The Hash Table has the following entries" << endl;
  for (int i = 0; i < tableSize; i++)
  {
    cout << i << ": ";
    if (dataTable[i].isEmpty())
      cout << "_";
    else
    {
      dataTable[i].gotoBeginning();
      do
      {
        cout << dataTable[i].getCursor().getKey() << " ";
      } while (dataTable[i].gotoNext());
    }
    cout << endl << endl;
  }
}
