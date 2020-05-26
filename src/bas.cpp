#include "bas.h"

using namespace std;

	int basic::counter = 0; // number of created via let variables
	map<int, int> basic::prev; // line number/ram slot for command
	int basic::pr = -1e9; // previous line
	int basic::ram = -1; // number of used ram slots
	map<string, int> basic::var; // variable/ram slot for it
	int basic::find_closing(string s, int opening) {
		int _new = 0;
		for (int it = opening + 1; it < s.size(); it++)
			if (s[it] == '(') _new++;
			else if (s[it] == ')') {
				_new--;
				if (_new == -1) return it;
			}
	}
	bool basic::is_operation(char ch) {
		if (ch == '/' or ch == '*' or ch == '+' or ch == '-') return true;
		return false;
	}
	bool basic::is_number(string s) {
		for (auto it : s) 
			switch (it) {
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					break;
				default:
					return false;
			}
		return true;
	}
	int basic::get_left_index(string s, int op) {
		int left = op - 1;
		while (left != -1) {
			if (is_operation(s[left])) return left + 1;
			left--;
		}
		return left + 1;
	}
	int basic::get_right_index(string s, int op) {
		int right = op + 1;
		while (right != s.size()) {
			if (is_operation(s[right])) return right - 1;
			right++;
		}
		return right - 1;
	}
	string basic::create(string& variable) {
		ram++;
		string result = to_string(ram) + " JUMP " + to_string(ram + 2) + "\n";
		ram++;
		var['/' + to_string(ram)] = ram;
		result += to_string(ram) + " =\t" + variable + "\n";
		variable = '/' + to_string(ram);
		return result;
	}
	string basic::micro_math(string& s, char op) {
		string result;
		auto operation = s.find_first_of(string(1, op));
		string var1 = s.substr(get_left_index(s, operation), operation - get_left_index(s, operation));
		string var2 = s.substr(operation + 1, get_right_index(s, operation) - operation);
		var1.erase(remove(var1.begin(), var1.end(), ' '), var1.end());
		var2.erase(remove(var2.begin(), var2.end(), ' '), var2.end());
		if (is_number(var1)) 
			result += create(var1);
		if (is_number(var2)) 
			result += create(var2);
		string command;
		if (op == '/') command = " DIVIDE\t";
		else if (op == '*') command = " MUL\t";
		else if (op == '+') command = " ADD\t";
		else if (op == '-') command = " SUB\t";
		ram++;
		result += to_string(ram) + " LOAD\t" + to_string(var[var1]) + "\n";
		ram++;
		result += to_string(ram) + command + to_string(var[var2]) + "\n";
		string temp;
		if (var1.find_first_of('/') == string::npos and var2.find_first_of('/') == string::npos) {
			ram++;
			result += to_string(ram) + " JUMP\t" + to_string(ram + 2) + "\n";
			ram++;
			temp = '/' + to_string(ram);
			var[temp] = ram;
		} else if (var1.find_first_of('/') != string::npos) {
			temp = var1;
		} else if (var2.find_first_of('/') != string::npos) {
			temp = var2;
		}
		ram++;
		s = s.substr(0, get_left_index(s, operation)) + temp + s.substr(get_right_index(s, operation) + 1);
		result += to_string(ram) + " STORE\t" + to_string(var[temp]) + "\n";
		return result;
	}
	string basic::do_math(string s) {
		auto opening = s.find_first_of('(');
		string result;
		while (opening != string::npos) {
			ram++;
			result += to_string(ram) + " JUMP\t" + to_string(ram + 2) + "\n";
			string temp = '/' + to_string(ram);
			var[temp] = ram;
			int closing = find_closing(s, opening);
			result += do_math(s.substr(opening + 1, closing - opening - 1));
			s = s.substr(0, opening) + temp + s.substr(closing + 1);
			ram++;
			result += to_string(ram) + " STORE\t" + to_string(var[temp]) + "\n";
			opening = s.find_first_of('(');
		}
		while (s.find_first_of('/') != string::npos)
			result += micro_math(s, '/');
		while (s.find_first_of('*') != string::npos)
			result += micro_math(s, '*');
		while (s.find_first_of('+') != string::npos)
			result += micro_math(s, '+');
		while (s.find_first_of('-') != string::npos)
			result += micro_math(s, '-');
		if (is_number(s))
			result += create(s);
		ram++;
		result += to_string(ram) + " LOAD\t" + to_string(var[s]) + "\n";
		return result;
	}
	pair<int, string> basic::translate(string line, bool _if) {
			istringstream s(line);
			string number = "-1", todo_todo; // todo_todo - whats already been done
			pair<int, string> ans;
			if (not _if) {
				s >> number;
				if (stoi(number) < pr) {
					ans = make_pair(-1, "");
					return ans; // wrong line order
				} else pr = stoi(number);
				todo_todo += number + ' ';
			}
			string command;
			s >> command;
			todo_todo += command + ' ';
			if (command == "END") {
				ram++;
				prev[stoi(number)] =  ram;
				ans = make_pair(1, to_string(ram) + " HALT\t" + "00");
				ram++;
				return ans;
			} else if (command == "REM") {
				prev[stoi(number)] =  -1;
			} else if (command == "INPUT") {
				ram += 3;
				string operand;
				s >> operand;
				if (operand.size() > 1 and not isupper(operand[0])) {
					ans = make_pair(-2, "");
					return ans; // wrong variable name
				}
				var[string(1, operand[0])] = ram;
				prev[stoi(number)] =  ram - 2;
				ans = make_pair(1, to_string(ram - 2) + " READ\t" + to_string(ram) + "\n" + to_string(ram - 1) + " JUMP\t" + to_string(ram + 1) + "\n");
				return ans;
			} else if (command ==  "OUTPUT") {
				ram++;
				string operand;
				s >> operand;
				if (operand.size() > 1 and not isupper(operand[0])) return make_pair(-2, ""); // wrong variable name
				if (var.count(string(1, operand[0])) != 0) {
					// exists
					prev[stoi(number)] =  ram;
					ans = make_pair(1, to_string(ram) + " WRITE\t" + to_string(var[string(1, operand[0])]) + "\n");
					return ans;
				} else {
					// doesnt exist -> create, make it zero and write
					ram += 2;
					var[string(1, operand[0])] = ram;
					prev[stoi(number)] =  ram - 2;
					ans = make_pair(1, to_string(ram - 2) + " =\t" + "0" + "\n" +  
					to_string(ram - 1) + " WRITE\t" + to_string(var[string(1, operand[0])]) + "\n");
					return ans;
				}
			} else if (command == "GOTO") {
				ram++;
				int operand;
				s >> operand;
				ans = make_pair(1, to_string(ram) + " JUMP\t" + '/' + to_string(operand) + "\n");
				ram++;
				return ans;
			} else if (command == "LET") {
				string variable;
				s >> variable;
				todo_todo += variable + ' ';
				if (variable.size() > 1 and not isupper(variable[0])) return make_pair(-2, ""); // wrong variable name
				if (var.count(string(1, variable[0])) != 0) {
					// exists
					ans = make_pair(-3, ""); // variable already exists
					return ans;
				} else {
					// doesnt exist
					counter++;
					var[string(1, variable[0])] = 100 - counter;
					string result = to_string(100 - counter) + " =\t" + "0" + "\n"; // create and make it zero
					string store;
					s >> store;
					todo_todo += store + ' ';
					if (store == "") { 
						ans = make_pair(1, result);
						return ans;
					} else if (store[0] == '=' and store.size() == 1) {
						string str = s.str().substr(todo_todo.size());
						result += do_math(str);
						ram++;
						result += to_string(ram) + " STORE\t" + to_string(var[string(1, variable[0])]) + "\n";
						ans = make_pair(1, result);
						return ans;
					}
					ans = make_pair(-4, ""); // unable to create variable
					return ans;
				}
			} else if (command == "IF") {
				string temp, cond, result;
				bool f1 = false;
				int oper = -1;
				while (true) { // while operation and variable alternate
					s >> temp;
					if (not f1 and (is_number(temp) or (temp.size() == 1 and isupper(temp[0])))) {
						cond += temp + ' ';
						f1 = true;
					} else if (f1 and is_operation(temp[0]) and temp.size() == 1) {
						cond += temp + ' ';
						f1 = false;
					} else if (f1 and temp != "<" and temp != ">" and temp != "==" and not is_operation(temp[0])) 
						break;
					else if (f1 and temp == "==") {
						cond += temp + ' ';
						oper = 0;
						f1 = false;
					} else if (f1 and temp == "<") {
						cond += temp + ' ';
						oper = 1;
						f1 = false;
					} else if (f1 and temp == ">") { 
						cond += temp + ' ';
						oper = 2;
						f1 = false;
					}	
				}
				temp = cond;
				todo_todo += temp;
				if (oper == 0) {
					auto op = temp.find_first_of("==");
					string var1 = temp.substr(0, op);
					string var2 = temp.substr(op + 2);
					if (var2.size() > 2) 
						var2 = '(' + var2 + ')';
					string math = var1 + "- " + var2;
					result += do_math(math);
					prev[stoi(number)] =  ram;
					ram++;
					result += to_string(ram) + " JZ\t" + to_string(ram + 2) + "\n";
				} else if (oper == 1) {
					auto op = temp.find_first_of("<");
					string var1 = temp.substr(0, op);
					string var2 = temp.substr(op + 2);
					if (var2.size() > 2) 
						var2 = '(' + var2 + ')';
					string math = var1 + "- " + var2;
					result += do_math(math);
					prev[stoi(number)] =  ram;
					ram++;
					result += to_string(ram) + " JNEG\t" + to_string(ram + 2) + "\n";
				} else if (oper == 1) {
					auto op = temp.find_first_of(">");
					string var1 = temp.substr(0, op);
					string var2 = temp.substr(op + 2);
					if (var2.size() > 2) 
						var2 = '(' + var2 + ')';
					string math = var2 + "- " + var1;
					result += do_math(math);
					prev[stoi(number)] =  ram;
					ram++;
					result += to_string(ram) + " JNEG\t" + to_string(ram + 2) + "\n";
				}
				ram++;
				int jump_to = ram;
				string str = s.str().substr(todo_todo.size());
				pair<int, string> todo = translate(str, true);
				result += to_string(jump_to) + " JUMP\t" + to_string(ram + 1) + "\n";
				result += todo.second ;
				ans = make_pair(1, result);
				return ans;
			}
			ans = make_pair(-5, ""); // wrong command
			return ans;
	}
	void basic::read(string input, string output) {
		ifstream in(input);
		ofstream out(output);
		string as;
		while (!in.eof()) {
			string s;
			getline(in, s);
			pair<int, string> result = translate(s, false);
			as += result.second;
		}
		int a;
		while (as.find_first_of('/') != string::npos) {
			a = as.find_first_of('/');
			int count = 0;
			char c = '/';
			while (a + count < as.size()) {
				if (as[a + count] == '\n') break;
				count++;
			}
			as = as.substr(0, a) + to_string(prev[stoi(as.substr(a + 1, a + count))]) + as.substr(a + count);
		}
		// while (as.find_first_of('@') != string::npos) {
		// 	a = as.find_first_of('@');
		// 	int count = 0;
		// 	char c = '/';
		// 	while (a + count < as.size()) {
		// 		if (as[a + count] == '\n') break;
		// 		count++;
		// 	}
		// 	as = as.substr(0, a) + to_string(ram++) + as.substr(a + count);
		// }
		out << as;
		in.close();
		out.close();
	}

int main(int argc, char** argv) {
	string in = argv[1];
	string out = argv[2];
	basic::read(in, out);
}