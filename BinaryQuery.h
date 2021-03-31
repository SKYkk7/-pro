#ifndef BINARYQUERY
#define BINARYQUERY
#include "Query_base.h"
#include "Query.h"

//Ҳ��һ��������࣬�����������������������
class BinaryQuery: public Query_base
{
protected:
	BinaryQuery(const Query& l, const Query& r, std::string s): lhs(l), rhs(r), opSym(s) {}
	//����̳ж����Ĵ�����rep()��eval����δ�̳У�����ȻΪ�������
	std::string rep() const { return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")"; }

	Query lhs, rhs;
	std::string opSym;
};
#endif // !BINARYQUERY

