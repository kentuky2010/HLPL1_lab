#include <'std_lib_facilities.h'>

//This function compiled.
void swap_v(int a, int b)
{
	int temp; temp = a, a = b; b = temp;
}

//This function compiled.
void swap_r(int& a, int& b)
{
	int temp; temp = a, a = b; b = temp;
}

//This function couldn't compile because the memory of a and b are constant
/*
void swap_cr(const int& a, const int& b)
{
	int temp; temp = a, a = b; b = temp;
}
*/

int main()
{
	int x = 7;
	int y = 9;
	swap_v(x, y); //This function compiles, but x and y does not swap
	swap_r(x, y); //This function compiles, while x and y swaps.
	swap_v(7, 9); //Function is compiled, but they cannot be swapped.
	swap_r(7, 9); // Function cannot be compiled as they are of different types.
	const int cx = 7;
	const int cy = 9;
	swap_v(cx, cy); //Function will be compiled, but they do not actually swap.
	swap_r(cx, cy);  //Function can not be compiled as they are not of the same type.
	swap_v(7.7, 9.9); //Function can be compiled, but they do not swap.
	swap_r(7.7, 9.9); //Function cannot be compiled as they are of different types.
	double dx = 7.7;
	double dy = 9.9;
	swap_v(dx, dy); //Function can be compiled, but they do not actually swap.
	swap_r(dx, dy);  //Function can not be compiled as they are not of the same type.
	swap_v(7.7, 9.9); //Function can be compiled, but they do not actually swap.
	swap_r(7.7, 9.9); //Function can not be compiled as they are not of the same type.
	cout << "x = " << x << endl;
	cout << "y = " << y << endl;
	cout << "cx = " << cx << endl;
	cout << "cy = " << cy << endl;
	cout << "dx = " << dx << endl;
	cout << "dy = " << dy << endl;
	return 0;
}