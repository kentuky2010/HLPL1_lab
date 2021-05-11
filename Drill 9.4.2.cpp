#include "std_lib_facilities.h"
// Drill 9.4.2
struct Date
{
	int y,m,d;
	Date (int yy, int mm, int dd)
	{
		if (yy < 0) error("Invalid year");
		if (mm < 1 || mm > 12) error("Invalid month");
		if (dd < 1 || dd > 31) error("Invalid date");
		y = yy;
		m = mm;
		d = dd;
	}

	void add_day(int n)
	{
		d += n;
		while (d > 31)
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
	return os << d.y << "." << d.m << "." << d.d;
}

void f()
try {

	Date today = { 1978, 6, 25 };
	cout << today << endl;
	Date tomorrow = today;
	tomorrow.add_day(1);
	cout << tomorrow << endl;
}
catch (exception& e) {
	cerr << e.what() << endl;
}

int main()
{
	f();
	return 0;
}
