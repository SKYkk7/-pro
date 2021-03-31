#ifndef NOTQUERY
#define NOTQUERY
#include "Query_base.h"
#include "query.h"

class NotQuery: public Query_base
{
	friend Query operator~(const Query&);
	NotQuery(const Query& q) : query(q) {}
	//�������м̳ж����Ĵ��麯��
	QueryResult eval(const TextQuery&) const;
	std::string rep() const { return "~(" + query.rep() + ")"; }

	Query query;
};
inline Query operator~(const Query& noque)
{
	return std::shared_ptr<Query_base>(new NotQuery(noque));
}
#endif // !1