#include "NotQuery.h"

QueryResult NotQuery::eval(const TextQuery& text) const
{
	auto result = query.eval(text);
	auto ret_lines = std::shared_ptr<std::set<line_no>>();
	//beg��endΪ���ҵ����кų��ֵķ�Χ
	auto beg = result.begin();  
	auto end = result.end();
	auto sz = result.get_file().size();   //�ļ����к�
	
	for (std::size_t n = 0; n != sz; ++n)
	{
		if (beg == end || *beg != n)
			ret_lines->insert(n);
		else if (beg != end)
			++beg;
	}
	return QueryResult(rep(), ret_lines, result.get_file());
}