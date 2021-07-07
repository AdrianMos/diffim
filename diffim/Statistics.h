#pragma once
#include "pch.h"

#include "ComparableEntity.h"

// Image comparison statistics: total images, identical images, different images...
class Statistics {
  public:
	void add_status(ComparisonStatus status);
	string to_string();

	void print();

    int total();
    int identical() { return _identical; };
    int different() { return _different; };
    int missing() { return _missing; };
    int not_compared() { return _not_compared; };    

  private:
	int _identical{0};
	int _different{0};
	int _missing{0};
	int _not_compared{0};
};