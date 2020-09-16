#pragma once

class Coordinate
{
private:
    int row;
    int column;

public:
    class Builder
    {
    private:
        int row;
        int column;
        
    public:
        Builder();
        Builder& withRow(int const _row);
        Builder& withColumn(int const _column);
        Coordinate build();
    };

    static Builder builder();
    int const getRow();
    int const getColumn();

private:
    Coordinate(int _row, int _column);
};