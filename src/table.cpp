// table.cpp
// Library for tabulating data
// Reinier E.
// revangel@sfu.ca

#ifdef TABLE_H
#include "../include/table.h"
#include <iomanip>
#include <assert.h>

// Helper functions
template<class T>
int Table<T>::getMaxColWidth(int row)
{
    int maxLength = 0;

    // Since Headings is a separate vector, let 
    // a row = -1 represent it
    if (row == -1)
        for (int col = 0; col < numColumns; col++)
        {
            if ((int)Headings[col].length() > maxLength)
                maxLength = Headings[col].length();
        }
    else if (row > 0 && row < numRows)
    {
        for (int col = 0; col < numColumns; col++)
        {
            if ((int)Rows[row][col].length() > maxLength)
                maxLength = Rows[row][col].length();
        }
    }
    return maxLength;
}

template<class T>
void Table<T>::updateWidth(int row)
{
    if(getMaxColWidth(row) > fieldWidth)
        setFieldWidth(getMaxColWidth(row));
}
    
template<class T>
void Table<T>::printHorizontalLine()
{
    int borderWidth = Border.length();

    // Get to the middle of the table
    for (int i = 0; i < borderWidth; i++)
        std::cout << " ";

    // The total span of the table will consist of the
    // fieldWidth (currently uniform) plus n-1 borders
    // in between
    int tableSpan = fieldWidth * numColumns + 
                    (numColumns-1)*borderWidth;
    
    for (int i = 0; i < tableSpan; i++)
        std::cout << "-";

    // No need to have a symmetrical operation to the
    // initial spacing, just end the line
    std::cout << std::endl;
}

template<class T>
void Table<T>::printAlignLeft(std::string string)
{
    assert(fieldWidth > 0);
    std::cout << string;
    for (int i = 0; i < (fieldWidth-(int)string.length()); i++)
        std::cout << " ";

}

template<class T>
void Table<T>::printAlignRight(std::string string)
{
    assert(fieldWidth > 0);
    for (int i = 0; i < (fieldWidth-(int)string.length()); i++)
        std::cout << " ";
    std::cout << string;
}

template<class T>
void Table<T>::printAlignCenter(std::string string)
{
    assert(fieldWidth > 0);

    int middle = ( fieldWidth-(int)string.length() ) / 2;
    for (int i = 0; i < middle; i++)
        std::cout << " "; // get to the middle of the column
    
    std::cout << string;

    int currentIndex = (int)string.length() + middle;
    while(currentIndex < fieldWidth)
    {
        std::cout << " ";
        currentIndex++;
    }
}

// Constructors
template<class T>
Table<T>::Table()
{
    numColumns = 0;
    numRows = 0;
    fieldWidth = 0;
    Border = "|";
    Name = "Table";
}

template<class T>
Table<T>::Table(std::string name)
{
    numColumns = 0;
    numRows = 0;
    fieldWidth = 0;
    Border = "|";
    Name = name;
}

template<class T>
int Table<T>::getNumCols()
{
    return numColumns;
}

template<class T>
int Table<T>::getNumRows()
{
    return numRows;
}

template<class T>
std::string Table<T>::getColName(int col)
{
    return Headings[col];
}

template<class T>
int Table<T>::getFieldWidth()
{
    return fieldWidth;
}

template<class T>
std::string Table<T>::getBorder()
{
    return Border;
}

template<class T>
std::string Table<T>::getName()
{
    return Name;
}

// Procedural Accessors
template<class T>
void Table<T>::printTable()
{
    std::cout << std::endl;
    std::cout << Name << ": " << std::endl;
    printHorizontalLine();
    printColumnHeadings();
    printHorizontalLine();
    printRows();
    printHorizontalLine();
    std::cout << std::endl;
}

template<class T>
void Table<T>::printColumnHeadings()
{
    for (int col = 0; col < numColumns; col++)
    {
        std::cout << Border;
        printAlignCenter(Headings[col]);

        // By design, each iteration will print
        // a border first and then the data
        // So the last one has to also print a 
        // border to the right
        if(col == numColumns-1)
            std::cout << Border;
    }
    std::cout << std::endl;
}

template<class T>
void Table<T>::printRows()
{
    for(int row = 0; row < (int)Rows.size(); row++)
        printRow(row);
}


template<class T>
void Table<T>::printRow(int row)
{
    if (!(row < 0 || row >= numRows))
    {
        for (int col = 0; col < numColumns; col++)
        {
            std::cout << Border;
            printAlignCenter(Rows[row][col]);

            // By design, each iteration will print
            // a border first and then the data
            // So the last one has to also print a 
            // border to the right
            if (col == numColumns - 1)
            {   
                std::cout << Border << std::endl;
            }
        }
    }
}

// Mutators
template<class T>
void Table<T>::addColumnHeading(std::string heading)
{
    Headings.push_back(heading);
    numColumns++;
    updateWidth(-1);
}

template<class T>
void Table<T>::addRow(std::vector<T> row)
{
    Rows.push_back(row);
    numRows++;
    updateWidth(numRows-1);
}

template<class T>
void Table<T>::addEmptyRow(std::vector<T> eRow)
{ 
    Rows.push_back(eRow);
    numRows++;
}

template<class T>
void Table<T>::addColumn(std::vector<std::string> column, std::string colName)
{
    // At the moment, it will only be possible to add a column to the right
    addColumnHeading(colName);

    // To add the column, all the elements in the column have to be
    // appended onto the end of each row (where this new column is)
    // But if this new column has more rows than the existing columns
    // then new rows will have to be created. The existing columns
    // will then have a filler character inserted for these new rows
    int extraRows = (int)column.size() - numRows;
    if(extraRows > 0)
    {
        // Filler for the existing columns
        std::vector<std::string> newEmptyRow;
        for (int i = 0; i < numColumns-1; i++) // Note numColumns already updated above
            newEmptyRow.push_back("");
        for (int i = 0; i < extraRows; i++)
        {
            addEmptyRow(newEmptyRow); 
        }
    }
    
    assert(numRows >= (int)column.size());
    // The table should now have the right amount of rows
    // so append the column contents to the end of each row
    // Note that we're indexing by column size because if we 
    // use numRows, then we'd be adding undefined elements if
    // the column is actually shorter than the rest
    for (int row = 0; row < (int)column.size(); row++)
    {
        Rows[row].push_back(column[row]);
    }

    // So if the column was shorter, then fill the rest of its empty rows
    if (extraRows < 0)
    {
        for (int row = (int)column.size(); row < numRows; row++)
        {
            Rows[row].push_back("");    
        }
    }
}

template<class T>
void Table<T>::replaceAllHeadings(std::vector<std::string> newHeadings)
{
    Headings = newHeadings;
    numColumns = (int)newHeadings.size();
    updateWidth(-1);
}

template<class T>
void Table<T>::replaceAllRows(std::vector<std::vector<std::string> > newRows)
{
    Rows = newRows;
    numRows = (int)newRows.size();
    for (int i = 0; i < numRows; i++)
        updateWidth(i);
}

template<class T>
void Table<T>::setFieldWidth(int newWidth)
{
    fieldWidth = newWidth;
}

template<class T>
void Table<T>::setBorder(std::string newBorder)
{
    Border = newBorder; 
}

#endif
