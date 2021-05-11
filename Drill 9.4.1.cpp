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
	if (m < 1 || m > 12) error("Invalid date");
	if (d < 1 || d > 31) error("Invalid month");

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

int main()
{
	Date today;
	init_day(today, 1978, 6, 25);
	cout << today << "\n";
	Date tomorrow = today;
	add_day(tomorrow, 1);
	cout << tomorrow << "\n" ;
	return 0;
}