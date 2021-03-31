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
		std::size_t n = file.size() - 1;   // ��ǰ����
		std::string words;
		std::stringstream lineStream(line);

		while (lineStream >> words)  //������ÿ�����ʣ�������ʲ���wordMap�Դ�Ϊ�±���wordMap�����һ��
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
	//û���ҵ�ʱ������һ��ָ���set��ָ��
	static std::shared_ptr<std::set<line_no>> noData(new std::set<line_no>());

	auto loc = wordMap.find(words);
	if (loc == wordMap.end())   
		return QueryResult(words, noData, file);  //û���ҵ�ʱ
	else 
		return QueryResult(words, loc->second, file);   //�ҵ�ʱ
}