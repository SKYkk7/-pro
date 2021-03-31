#ifndef BINARYQUERY
#define BINARYQUERY
#include "Query_base.h"
#include "Query.h"

//也是一个抽象基类，保存操作两个运算对象的数据
class BinaryQuery: public Query_base
{
protected:
	BinaryQuery(const Query& l, const Query& r, std::string s): lhs(l), rhs(r), opSym(s) {}
	//定义继承而来的春旭函数rep()，eval函数未继承，其依然为抽象基类
	std::string rep() const { return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")"; }

	Query lhs, rhs;
	std::string opSym;
};
#endif // !BINARYQUERY

