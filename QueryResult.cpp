#include "QueryResult.h"

std::ostream& print(std::ostream& os, const QueryResult& s)
{
	os << s.sought << "出现了" << s.find_line->size() << "次" << std::endl;
	//打印单词出现的行数
	for (auto& index : *s.find_line)  //打印出出现的每一行
	{
		os << "\t(line " << index + 1 << ") ";
		const StrBlobPtr wp(s.file, index);
		os << wp.deref() << "\n";
	}

	return os;
}