#ifndef STRBLOB_H
#define STRBLOB_H

#include <vector>
#include <string>
#include <initializer_list>
#include <memory>
#include <stdexcept>

class StrBlobPtr;
class StrBlob
{
	friend StrBlobPtr;
public:
	using size_type = std::vector<std::string>::size_type;

	StrBlob() : data(std::make_shared<std::vector<std::string>>()) {}    //默认构造函数，进行值初始化
	StrBlob(std::initializer_list<std::string> il);

	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }

	//添加元素和移除元素
	void push_back(const std::string& t) { data->push_back(t); }
	void pop_back();

	//元素访问
	std::string& front();
	std::string& back();

	// 与StrBlobPtr的接口
	StrBlobPtr begin();
	StrBlobPtr end();

private:
	std::shared_ptr<std::vector<std::string>> data;

};

//构造函数
inline StrBlob::StrBlob(std::initializer_list<std::string> il): 
	   data(std::make_shared<std::vector<std::string>>(il)) {}

class StrBlobPtr
{
	friend bool eq(const StrBlobPtr&, const StrBlobPtr&);
public:
	StrBlobPtr():curr(0) {}
	StrBlobPtr(const StrBlob& a, size_t sz = 0): wptr(a.data), curr(sz) {}

	std::string& deref() const;    //解引用
	StrBlobPtr& incr();
	StrBlobPtr& decr();
private:
	// 若检查成功，check返回一个指向vector的shared_ptr
	std::shared_ptr<std::vector<std::string>> check(std::size_t, const std::string&) const;
	std::weak_ptr<std::vector<std::string>> wptr;    //
	std::size_t curr;    // 在数组当前位置
};
inline
std::string& StrBlobPtr::deref() const
{
	auto p = check(curr, "取消引用结束");
	return (*p)[curr];
}

inline 
std::shared_ptr<std::vector<std::string>> StrBlobPtr::check(std::size_t i, const std::string& s) const
{
	auto ret = wptr.lock();    //判断wptr所指向的vector还存在吗
	if (!ret)
		throw std::runtime_error("未绑定StrBlonPtr");
	if (i >= ret->size())
		throw std::out_of_range(s);

	return ret;   //否则返回指向vector的shared_ptr
}

inline
StrBlobPtr& StrBlobPtr::incr()   //前缀返回对增量对象的引用
{
	check(curr, "递增到StrBlobPtr的末尾");
	++curr;
	return *this;
}

inline
StrBlobPtr& StrBlobPtr::decr()
{
	--curr;
	check(-1, "递减到StrBlobPtr的开始");
	return *this;
}

inline 
StrBlobPtr StrBlob::begin()
{
	return StrBlobPtr(*this);
}

inline
StrBlobPtr StrBlob::end()
{
	auto ret = StrBlobPtr(*this, data->size());
	return ret;
}

inline 
void StrBlob::pop_back()
{
	if (!data->empty())
		data->pop_back();
}

inline 
std::string& StrBlob::front()
{
	std::string s = data->front();
	return s;
}

inline
std::string& StrBlob::back()
{
	std::string s = data->front();
	return s;
}

inline
bool eq(const StrBlobPtr& lhs, const StrBlobPtr& rhs)
{
	auto l = lhs.wptr.lock();
	auto r = rhs.wptr.lock();
	if (l == r)
		return (!r || lhs.curr == rhs.curr);
	else
		return false;
}
#endif // !STRBLOB_H

	