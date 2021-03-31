#include "QueryResult.h"

std::ostream& print(std::ostream& os, const QueryResult& s)
{
	os << s.sought << "������" << s.find_line->size() << "��" << std::endl;
	//��ӡ���ʳ��ֵ�����
	for (auto& index : *s.find_line)  //��ӡ�����ֵ�ÿһ��
	{
		os << "\t(line " << index + 1 << ") ";
		const StrBlobPtr wp(s.file, index);
		os << wp.deref() << "\n";
	}

	return os;
}