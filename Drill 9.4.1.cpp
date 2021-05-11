#include "std_lib_facilities.h"
// Drill 9.4.1
struct Date
{
	int y; //year
	int m; //month in year
	int d; //day in month
};

void init_day(Date& dd, int y, int m, int d)
{
	if (m < 1 || m > 12) error("Invalid month");
	if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
	{
		if (d < 1 || d > 31) error("Invalid date");
	}
	else if (m == 2)
	{
		if (d < 1 || d > 29) error("Invalid date");
	}
	else if (d < 1 || d > 30) error("Invalid date");
	

	dd.y = y;
	dd.m = m;
	dd.d = d;
}

void add_day(Date& dd, int n)
{
	dd.d += n;
	while (dd.d > 31) 
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
	return os << '(' << d.y << ',' << d.m << ',' << d.d << ')';
}

void f()
{
	Date today;
	init_day(today, 1978, 6, 25);
	cout << today << "\n";
	Date tomorrow = today;
	add_day(tomorrow, 1);
	cout << tomorrow << "\n";
}
int main()
{
	f();
	return 0;
}