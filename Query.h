#ifndef QUERY_H
#define QUERY_H
#include "QueryResult.h"
#include "TextQuery.h"
#include "Query_base.h"
#include "WordQuery.h"

class Query
{
	friend Query operator~(const Query&);
	friend Query operator|(const Query&, const Query&);
	friend Query operator&(const Query&, const Query&);
	
public:
	Query(const std::string& s): q(new WordQuery(s)) {}   // 构建一个新的WOrdQuery
	//接口函数
	QueryResult eval(const TextQuery& t) const { return q->eval(t); }
	std::string rep() const { return q->rep(); }
private:
	Query(std::shared_ptr<Query_base> base): q(base) {}
	std::shared_ptr<Query_base> q;   //
};
inline std::ostream& operator<<(std::ostream& os, const Query& query)
{
	os << query.rep();
}

#endif // !QUERY

