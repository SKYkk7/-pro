#ifndef TEXTQUERY
#define TEXTQUERY

#include "StrBlob.h"
#include <map>
#include <set>
#include <memory>
#include <fstream>

class QueryResult;
class TextQuery
{
public:
	using line_no = StrBlob::size_type;
	TextQuery(std::ifstream& fin);

	QueryResult query(const std::string&) const;  // 查询函数
private:
	StrBlob file;
	std::map<std::string, std::shared_ptr<std::set<line_no>>> wordMap;  //保存单词和其对赢得行数
};
#endif // !TEXTQUERY

