#include "std_lib_facilities.h"
// Drill 9.4.2
class Date
{
private:
	int y, m, d;
public:
	Date(int yy, int mm, int dd)
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
	int get_day()
	{
		return d;
	}
	void set_day(int dd)
	{
		if (dd < 0 || dd > 31) "Invalid day";
		d = dd;
	}
	int get_month()
	{
		return m;
	}
	void set_month(int mm)
	{
		if (mm < 0 || mm > 12) "Invalid month";
		m = mm;
	}
	int get_year()
	{
		return y;
	}
	void set_year(int yy)
	{
		if (yy < 0) "Invalid year";
		y = yy;
	}
};

ostream& operator<<(ostream& os, Date& d)
{
	return os <<  d.get_year() << "." << d.get_month() << "." << d.get_day();
}

void f()
try {
	Date today(1978, 6, 25);
	cout << today << "\n";
	Date tomorrow(today);
	tomorrow.add_day(1);
	cout << tomorrow << "\n";
}

catch (exception& e) {
	cerr << e.what() << "\n";
}

int main()
 {
	f();
	return 0;
}
