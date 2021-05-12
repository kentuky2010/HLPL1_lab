#include "std_lib_facilities.h"
//Drill 9.7.4
enum class Month
{
	Jan = 1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec
};

class Date
{
public:
	Date(int yy, Month mm, int dd);

	int day() const
	{
		return d;
	}

	Month month() const
	{
		return m;
	}
	int year() const
	{
		return y;
	}

	void add_day(int n);
	void add_month(int n);
	void add_year(int n);

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

void Date::add_day(int n)
{
	d += n;
	while (d > 31)
	{
		d -= 31;
		add_month(1);
	}
}

void Date::add_month(int n)
{
	int newMonth = int(m);
	newMonth += n;
	while (newMonth > 12)
	{
		newMonth -= 12;
		add_year(1);
	}
	m = Month(newMonth);
}

void Date::add_year(int n)
{
	y += n;
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