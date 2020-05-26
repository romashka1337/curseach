#include <bits/stdc++.h>

using namespace std;

class basic {
private:
	static int counter; // number of created via let variables
	static map<int, int> prev; // line number/ram slot for command
	static int pr; // previous line
	static int ram; // number of used ram slots
	static map<string, int> var; // variable/ram slot for it
	static int find_closing(string , int );
	static bool is_operation(char );
	static bool is_number(string );
	static int get_left_index(string , int );
	static int get_right_index(string , int );
	static string create(string& );
	static string micro_math(string& , char );
	static string do_math(string );
	static pair<int, string> translate(string , bool );
public:
	static void read(string , string output);
};