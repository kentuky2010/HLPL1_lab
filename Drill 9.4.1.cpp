#include "std_lib_facilities.h"
// Drill 9.4.1
struct Date
{
	int y, m, d;
};

void init_day(Date& dd, int y, int m, int d)
{
	if (y < 0) error("Invalid year");
	if (m < 1 || m > 12) error("Invalid month");
	if (d < 1 || d > 31) error("Invalid date");

	dd.y = y;
	dd.m = m;
	dd.d = d;
}

void add_day(Date& dd, int n)
{
	int m;
	dd.d += n;
	while (dd.d > m) 
	{
		dd.d -= 31;
		dd.m++;
		while (dd.m > 12)
		{
			dd.m -= 12;
			dd.y++;
		}
	}
}

ostream& operator<<(ostream& os, const Date& d)
{
	return os << d.y << "." << d.m << "." << d.d;
}

void f()
try{
	Date today;
	init_day(today, 1978, 6, 25);
	cout << today << "\n";
	Date tomorrow = today;
	add_day(tomorrow, 365);
	cout << tomorrow << "\n";
}

catch (exception& e) {
	cerr << e.what() <<"\n";
	return 1;
}

int main()
{
	f();
	return 0;
}
