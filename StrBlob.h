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

	StrBlob() : data(std::make_shared<std::vector<std::string>>()) {}    //Ĭ�Ϲ��캯��������ֵ��ʼ��
	StrBlob(std::initializer_list<std::string> il);

	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }

	//���Ԫ�غ��Ƴ�Ԫ��
	void push_back(const std::string& t) { data->push_back(t); }
	void pop_back();

	//Ԫ�ط���
	std::string& front();
	std::string& back();

	// ��StrBlobPtr�Ľӿ�
	StrBlobPtr begin();
	StrBlobPtr end();

private:
	std::shared_ptr<std::vector<std::string>> data;

};

//���캯��
inline StrBlob::StrBlob(std::initializer_list<std::string> il): 
	   data(std::make_shared<std::vector<std::string>>(il)) {}

class StrBlobPtr
{
	friend bool eq(const StrBlobPtr&, const StrBlobPtr&);
public:
	StrBlobPtr():curr(0) {}
	StrBlobPtr(const StrBlob& a, size_t sz = 0): wptr(a.data), curr(sz) {}

	std::string& deref() const;    //������
	StrBlobPtr& incr();
	StrBlobPtr& decr();
private:
	// �����ɹ���check����һ��ָ��vector��shared_ptr
	std::shared_ptr<std::vector<std::string>> check(std::size_t, const std::string&) const;
	std::weak_ptr<std::vector<std::string>> wptr;    //
	std::size_t curr;    // �����鵱ǰλ��
};
inline
std::string& StrBlobPtr::deref() const
{
	auto p = check(curr, "ȡ�����ý���");
	return (*p)[curr];
}

inline 
std::shared_ptr<std::vector<std::string>> StrBlobPtr::check(std::size_t i, const std::string& s) const
{
	auto ret = wptr.lock();    //�ж�wptr��ָ���vector��������
	if (!ret)
		throw std::runtime_error("δ��StrBlonPtr");
	if (i >= ret->size())
		throw std::out_of_range(s);

	return ret;   //���򷵻�ָ��vector��shared_ptr
}

inline
StrBlobPtr& StrBlobPtr::incr()   //ǰ׺���ض��������������
{
	check(curr, "������StrBlobPtr��ĩβ");
	++curr;
	return *this;
}

inline
StrBlobPtr& StrBlobPtr::decr()
{
	--curr;
	check(-1, "�ݼ���StrBlobPtr�Ŀ�ʼ");
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

	