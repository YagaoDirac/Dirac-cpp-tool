#include<vector>
#include<string>
#include<iostream>

class DCT_object
{
public:
	DCT_object() {};
	virtual ~DCT_object() {};

	virtual std::string type() { return "DCT_object"; };
};

class a:public DCT_object
{
public:
	a() {};
	virtual ~a() {};
	virtual std::string type()override { return "a"; };
	int aaa;
};
class b:public DCT_object
{
public:
	b() {};
	virtual ~b() {};
	virtual std::string type()override { return "b"; };
	float bbb;
};


class c
{
public:
	c() {};

	template<typename T>
	bool add(T* in)//input of this function cannot be const
	{
		//In this way, it's easy to do extra limitation.
		DCT_object* temp = dynamic_cast<DCT_object*>(in);
		if (temp) 
		{
			children.push_back(in); 
			return true;
		}
		else { return false; }
	};

	template<typename T>
	T* find()
	{
		for (auto iter = children.begin(); iter != children.end(); iter++)
		{
			T* temp = dynamic_cast<T*>(*iter);
			if (temp)return temp;
		}
		return nullptr;
	}

	std::vector<DCT_object*> children;

};

int main(int argc, char *argv[])
{
	a aa; aa.aaa = 123;
	b bb; bb.bbb = 1.23f;
	c cc;
	cc.add(&aa);
	cc.add(&bb);
	a* presult = cc.find<a>();

	std::cout << presult->type();

	system("pause");

	return 0;
}