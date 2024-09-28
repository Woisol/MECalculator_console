#include<string>
#include<sstream>
#include<stack>
using namespace std;
class Expression
{
	string expression;
public:
	string getExpression()const { return expression; }
	bool empty() { return expression.empty(); }
	void init(stringstream sstream) { sstream >> expression; }
	int calculate() {
		stack<int> operaters;
		for (int i = 0;i < expression.length();i++)
		{
			if (expression[i] >= '0' && expression[i] <= '9')
			{
				int num = 0;
				while (i < expression.length() && expression[i] >= '0' && expression[i] <= '9')
				{
					num = num * 10 + expression[i] - '0';
					i++;
				}
				operaters.push(num);
			}
			else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/')
			{
				int op2 = operaters.top();
				operaters.pop();
				int op1 = operaters.top();
				operaters.pop();
				if (expression[i] == '+')
				{
					operaters.push(op1 + op2);
				}
				else if (expression[i] == '-')
				{
					operaters.push(op1 - op2);
				}
				else if (expression[i] == '*')
				{
					operaters.push(op1 * op2);
				}
				else if (expression[i] == '/')
				{
					operaters.push(op1 / op2);
				}
			}
			else
			{
				continue;
			}
		}
		return operaters.top();
	}
}expression;
