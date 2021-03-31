#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <fstream>

#include "queryresult.h"
#include "textquery.h"
#include "query_base.h"
#include "query.h"
#include "andquery.h"
#include "orquery.h"

void runQuery(std::ifstream& infile)
{
	TextQuery q(infile);
	
	while (true)
	{
		std::cout << "输入单词查询，或q退出:" << std::endl;
		std::string s;
		if (!(std::cin >> s) || s == "q")
			break;
		Query query = Query("hello") | Query("is");
		print(std::cout, query.eval(q)) << std::endl;
	}
}

int main()
{
	std::ifstream file("D:\\project\\C++\\restart\\testt.txt");

	/*TextQuery tQuery(file);
	Query q = Query("hello") | Query("wind");
	std::cout << q;*/

	runQuery(file);
	return 0;
}