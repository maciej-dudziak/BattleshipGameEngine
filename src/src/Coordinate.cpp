#include "../Coordinate.h"

Coordinate::Coordinate(int _row, int _column) : row(_row), column(_column)
{
}

Coordinate::Builder::Builder()
{
}

Coordinate::Builder& Coordinate::Builder::withRow(int const _row)
{
    row = _row;
    return *this;
}

Coordinate::Builder& Coordinate::Builder::withColumn(int const _column)
{
    column = _column;
    return *this;
}

Coordinate Coordinate::Builder::build()
{
    return Coordinate(row, column);
}

Coordinate::Builder Coordinate::builder()
{
    return Builder();
}

int const Coordinate::getColumn()
{
    return column;
}

int const Coordinate::getRow()
{
    return row;
}