#ifndef QUERYRESULT
#define QUERYRESULT

#include <iostream>
#include <set>
#include <map>
#include <string>
#include "TextQuery.h"

class QueryResult
{
	friend std::ostream& print(std::ostream&, const QueryResult&);
public:
	QueryResult(const std::string& word, std::shared_ptr<std::set<TextQuery::line_no>> find_l, StrBlob f):
		sought(word), find_line(find_l), file(f) {}

	const StrBlob& get_file() const { return file; }

	std::set<TextQuery::line_no>::iterator begin() { return find_line->begin(); }
	std::set<TextQuery::line_no>::iterator end() { return find_line->end(); }
	//std::shared_ptr<std::set<TextQuery::line_no>> get_find_line() { return find_line; }   //
private:
	std::string sought;
	std::shared_ptr<std::set<TextQuery::line_no>> find_line;
	StrBlob file;
};

std::ostream& print(std::ostream&, const QueryResult&);

#endif // !QUERYRESULT

