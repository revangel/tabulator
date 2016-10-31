// tableTest.cpp
// Test suite for table
// Reinier E.
// revangel@sfu.ca

// Note: This test assumes a sensible table with std::string headings
// and int data in the cells
//
#include <iostream>
#include <string>

#include <assert.h>

#include "../include/table.h"

Table<std::string> makeATable(std::string name)
{
    std::cout << "Creating a new table. " << std::endl;
    Table<std::string> tbl(name);
    assert(tbl.getNumCols() == 0);
    assert(tbl.getNumRows() == 0);
    assert(tbl.getFieldWidth() == 0);
    assert(tbl.getName().compare(name) == 0);
    std::cout << "A new table has been created. " << std::endl;
    return tbl;
}

void initializeTableHeadings(Table<std::string>& table, std::vector<std::string> headings)
{
    std::cout << "Initializing " << table.getName() << "'s headings. " << std::endl;
    table.replaceAllHeadings(headings);
    for (int col = 0; col < table.getNumCols(); col++)
    {
        assert(table.getColName(col).compare(headings[col]) == 0);
        std::cout << table.getColName(col) << " ";
    }
    std::cout << std::endl;
    std::cout << table.getName() << "'s headings have been initialized: " << std::endl;
}

void askForHeadings(std::vector<std::string>& headings)
{
    std::cout << "Enter headings and enter /hd when done. " << std::endl;
    
    std::string temp;
    bool active = true;
    while(active)
    {
        std::cout << "Enter a heading: ";
        getline(std::cin, temp);
        if (temp.compare("/hd") == 0)
        {
            active = false;
            break;
        }
        headings.push_back(temp);
    }
}

void askForRows(Table<std::string>& table)
{
    bool active = true;
    while(active)
    {
        std::cout << "Enter value for " << std::endl;

        std::vector<std::string> row;
        for (int col = 0; col < table.getNumCols(); col++)
        {
            std::cout << table.getColName(col) << ": ";
            std::string val;
            getline(std::cin, val);
            row.push_back(val);
        }
        table.addRow(row);

        std::cout << "Another line? (y/n) " << std::endl;
        std::string ans;
        getline(std::cin, ans);
        if (ans.compare("n") == 0)
            active = false;
    }
}

void askForNewColumn(Table<std::string>& table)
{
    std::string opt;
    std::cout << "Do you want to add another column? (y/n)";
    getline(std::cin, opt);

    if (opt.compare("y") == 0)
    {
        std::string name;
        std::cout << "What's the column name? " << std::endl;
        getline(std::cin, name);
        
        std::vector<std::string> col;

        bool active = true;
        while (active)
        {
            std::cout << "Enter a row value (/col to end): ";
            std::string val;
            getline(std::cin, val);
            if (val.compare("/col") == 0)
            {
                active = false;
                break;
            }
            col.push_back(val);
        }

        table.addColumn(col, name);
        std::cout << "Column " << name << " added." << std::endl;
    }
}

int main()
{
   Table<std::string> test = makeATable("Test Table");
   std::vector<std::string> headings;
   
   askForHeadings(headings);
   
   initializeTableHeadings(test, headings);

   askForRows(test);

   askForNewColumn(test);

   test.printTable();

   return 0;
}


