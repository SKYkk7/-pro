#include <iostream>
#include <sstream>
#include <iterator>
#include "TextQuery.h"
#include "QueryResult.h"

TextQuery::TextQuery(std::ifstream& fin): file(StrBlob()), wordMap(std::map<std::string, std::shared_ptr<std::set<line_no>>>())
{
	std::string line;
	while (getline(fin, line))
	{
		file.push_back(line);
		std::size_t n = file.size() - 1;   // 当前行数
		std::string words;
		std::stringstream lineStream(line);

		while (lineStream >> words)  //对行中每个单词，如果单词不在wordMap以此为下标在wordMap中添加一项
		{
			std::shared_ptr<std::set<line_no>>& sp_lines = wordMap[words];
			if (!sp_lines)
			{
				sp_lines.reset(new std::set<line_no>());
			}
			sp_lines->insert(n);
		}
	}
}

QueryResult TextQuery::query(const std::string& words) const
{
	//没有找到时，返回一个指向次set的指针
	static std::shared_ptr<std::set<line_no>> noData(new std::set<line_no>());

	auto loc = wordMap.find(words);
	if (loc == wordMap.end())   
		return QueryResult(words, noData, file);  //没有找到时
	else 
		return QueryResult(words, loc->second, file);   //找到时
}