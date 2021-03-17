#include "../../std_lib_facilities.h"

constexpr char number = '8';
constexpr char quit = 'quit';
constexpr char print = ';';
constexpr char name = 'a';
constexpr char let = '#';//drill 7.10
const string declkey = "#";//drill 7.10
const string square = "sqrt";//drill 7.7
const string power = "pow";//drill 7.9
const string quitkey = "quit"; //drill 7.11

double expression();

class Variable {
public:
	string name;
	double value;
};

vector<Variable> var_table;

bool is_declared(string var) {
	for (const auto& v : var_table)
		if (v.name == var) return true;
	return false;
}

double define_name(string var, double val) {
	if (is_declared(var)) error(var, " declared twice");
	var_table.push_back(Variable{ var,val });
	return val;
}

double get_value(string s) {
	for (const auto& v : var_table)
		if (v.name == s) return v.value;
	error("get: undefined variable", s);
}

void set_value(string s, double d) {
	for (auto& v : var_table)
		if (v.name == s) {
			v.value = d;
			return;
		}
	error("set: undefined variable", s);
}

class Token {
public:
	char kind;
	double value;
	string name;
	Token() : kind(0) {}
	Token(char ch) : kind(ch), value(0) {}
	Token(char ch, double val) : kind(ch), value(val) {}
	Token(char ch, string n) : kind(ch), name(n) {}
};

class Token_stream {
public:
	Token_stream();
	Token get();
	void putback(Token t);
	void ignore(char c);
private:
	bool full;
	Token buffer;
};

Token_stream::Token_stream() :full(false), buffer(0) {}

void Token_stream::putback(Token t) {
	if (full) error("putback() into full buffer");
	buffer = t;
	full = true;
}

Token Token_stream::get() {

	if (full) {
		full = false;
		return buffer;
	}

	char ch;
	cin >> ch;

	switch (ch) {
	case print:
	case quit:
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case '=':
		return Token(ch);
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{
		cin.putback(ch);
		double val;
		cin >> val;
		return Token(number, val);
	}
	default:
	{
		if (isalpha(ch)) {
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch;
			cin.putback(ch);
			if (s == declkey) return Token{ let };
			else if (s == square) return Token('s');   // drill 7.7
			else if (s == power) return Token('p');    // drill 7.9
			else if (s == quitkey) return Token(quit); // drill 7.10
			else if (is_declared(s))
				return Token(number, get_value(s));
			return Token{ name,s };
		}
		error("Bad token");
	}
	}
}

void Token_stream::ignore(char c) {

	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;

	char ch = 0;
	while (cin >> ch)
		if (ch == c) return;
}

Token_stream ts;

double primary() {

	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{
		double d = expression();
		t = ts.get();
		if (t.kind != ')') error("')' expected");
		return d;
	}
	case number:
		return t.value;
	case '-':
		return -primary();
	case '+':
		return primary();
	case 's': //drill 7.7
	{
		char ch;
		double SquareRoot;
		if (cin >> ch && ch == '(') {
			SquareRoot = expression();
		}
		else error("The function must start with (!\n");
		if (ts.get().kind == ')') {

			if (SquareRoot >= 0)
				return sqrt(SquareRoot);

			else error("The value must bigger than 0!\n");//drill 7.8
		}
		else error("The function must end with )!\n");
		//function: sqrt(xa+by) with xa+by>0
	}
	case 'p':  // chapter 7.9
	{
		char ch;
		double Power;
		int power;
		if (cin >> ch && ch == '(') {
			Power = primary();
			if (cin >> ch && ch == ',') {
				power = narrow_cast<int>(primary());
			}
			else error("Comma(,) is needed between values");
		}
		else error("Enter (first)");
		if (cin >> ch && ch == ')') {
			return pow(Power, power);
		}
		else error("The function have to end with )");
	}
	default:
		error("Primary expected");
	}
}

double term() {

	double left = primary();
	Token t = ts.get();
	while (true) {
		switch (t.kind) {
		case '*':
			left *= primary();
			t = ts.get();
			break;
		case '/':
		{
			double d = primary();
			if (d == 0) error("divide by zero");
			left /= d;
			t = ts.get();
			break;
		}
		case '%':
		{
			double d = primary();
			if (d == 0) error("%: Zero oszto");
			left = fmod(left, d);
			t = ts.get();
			break;
			/*
			int i1 = narrow_cast<int>(left);
			int i2 = narrow_cast<int>(primary());
			if (i2 == 0) error ("%: Zero oszto");
			left = i1 % i2;
			t = ts.get();
			break;
			*/
		}
		default:
			ts.putback(t);
			return left;
		}
	}
}

double expression() {

	double left = term();
	Token t = ts.get();
	while (true) {
		switch (t.kind) {
		case '+':
			left += term();
			t = ts.get();
			break;
		case '-':
			left -= term();
			t = ts.get();
			break;
		default:
			ts.putback(t);
			return left;
		}
	}
}

void clean_up_mess() {
	ts.ignore(print);
}

double declaration() {
	Token t = ts.get();
	if (t.kind != name) error("name expected in declaration");
	string var_name = t.name;

	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", var_name);

	double d = expression();
	define_name(var_name, d);
	return d;
}

double statement() {
	Token t = ts.get();
	switch (t.kind) {
	case let:
		return declaration();
	default:
		ts.putback(t);
		return expression();
	}
}

void calculate() {

	/*	double val = 0;

		while (cin)
			try {

			Token t = ts.get();
			while (t.kind == print) t = ts.get();
			if (t.kind == quit) return;
			ts.putback(t);
			cout << "=" << statement() << endl;
			*/
	while (cin)
		try {
		Token t = ts.get();
		while (t.kind == print) t = ts.get();
		if (t.kind == quit) return;
		ts.putback(t);
		cout << "=" << statement() << endl;
	}
	catch (exception& e) {
		cerr << e.what() << endl;
		clean_up_mess();
	}
}

int main()

try {
	
	define_name("pi", 3.1415926535);
	define_name("e", 2.7182818284);
	define_name("k", 1000); // drill 7.6
	calculate();

	return 0;
}
catch (exception& e) {
	cerr << e.what() << endl;
	return 1;
}
catch (...) {
	cerr << "exception\n";
	return 2;
}
