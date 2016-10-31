// table.h
// Library for tabulating data
// Reinier E.
// revangel@sfu.ca

#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <vector>
#include <string>

template <class T>
class Table
{
    private:
        std::vector<std::string> Headings;
        std::vector<std::vector<std::string> > Rows;

        int numColumns;
        int numRows;
        int fieldWidth;
        std::string Border;
        std::string Name;

        int getMaxColWidth(int row); // Returns the longest string in a column
        void updateWidth(int row);
        void printHorizontalLine();
        void printAlignLeft(std::string string);
        void printAlignRight(std::string string);
        void printAlignCenter(std::string string);

        // For use in addColumns
        // Bypasses updateWidths in the standard addRow which currently 
        // breaks on empty rows since it's accessing the column index
        // before the column data has been pushed back
        void addEmptyRow(std::vector<T> eRow);

    public:
        Table(); // Default constructor
        Table(std::string name);

        // Functional Accessors
        int getNumCols();
        int getNumRows();
        int getFieldWidth();
        std::string getColName(int col);
        std::string getBorder();
        std::string getName();
       
        // Procedural Accessors
        void printTable();
        void printColumnHeadings();
        void printRows();
        void printRow(int row);
        void printCol(int col);

        // Mutators
        void addColumnHeading(std::string heading);
        void addRow(std::vector<T> row);
        void addColumn(std::vector<std::string> column, std::string colName);
        void replaceAllHeadings(std::vector<std::string> newHeadings);
        void replaceAllRows(std::vector<std::vector<std::string> > rows);
        void setFieldWidth(int newWidth);
        void setBorder(std::string newBorder);
};
#include "../src/table.cpp"
#endif
