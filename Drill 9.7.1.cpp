#include "std_lib_facilities.h"
//Drill 9.7.1
enum class Month
{
	Jan = 1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec
};

class Date
{
public:
	Date(int yy, Month mm, int dd);
	void add_day(int n)
	{
		d += n;
		while (d > 31)
		{
			d -= 31;
			m = Month(int(m)+1);
			m = (m == Month::Dec) ? Month::Jan : Month(int(m) + 1);
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
	Month get_month()
	{
		return m;
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
private:
	int y, d;
	Month m;
};
Date::Date(int yy, Month mm, int dd)
{
	if (yy < 0)
		cout << "Invalid year!";
	if (int(mm) > 12 || int(mm) < 1)
		cout << "Invalid month!";
	if (dd > 31 || dd < 1)
		cout << "Invalid day!" << "\n";
	else
	{
		y = yy; m = mm; d = dd;
	}
}
ostream& operator<<(ostream& os, Date& d)
{
	return os << d.get_year() << "." << int(d.get_month()) << "." << d.get_day();
}

void f()
try {
	Date today = { 1978, Month::Jun, 25 };
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
