#include "std_lib_facilities.h"
// Drill 9.4.2
struct Date
{
	int y,m,d;
	Date (int yy, int mm, int dd)
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
		y = yy;
		m = mm;
		d = dd;
	}

	void add_day(int n)
	{
		int max;
		d += n;
		if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
			max = 31;
		else if (m == 2)
			max = 29;
		else max = 30;
		while (d > m)
		{
			d -= 31;
			m++;
			while (m > 12)
			{
				m -= 12;
				y++;
			}
		}
	}
};

ostream& operator<<(ostream& os, const Date& d)
{
	return os << '(' << d.y << ',' << d.m << ',' << d.d << ')';
}

void f()
{
	Date today(1978, 6, 25);
	cout << today << "\n";
	cout << today << "\n";
}

int main()
try{
	f();
	return 0;
}

catch (exception& e) {
	cerr << e.what() << endl;
	return 1;
}