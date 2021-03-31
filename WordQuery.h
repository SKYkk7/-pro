#ifndef WORDQUERY
#define	WORDQUERY
#include "Query_base.h"
class WordQuery: public Query_base
{
	friend class Query;  //Query使用WordQuery的构造函数
private:
	WordQuery(const std::string& s): query_word(s) {}
private:
	QueryResult eval(const TextQuery& t) const { return t.query(query_word); }
	std::string rep() const { return query_word; }
	std::string query_word;  // 要查找的单词
};
#endif // !WORDQUERY

