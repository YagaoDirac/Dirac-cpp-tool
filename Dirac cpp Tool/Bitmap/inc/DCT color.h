#pragma once

//namespace in ms vs 2017 seems not work or what. Anyway I can't get this to work.
//namespace dct
//{
//	struct test
//	{
//		test() :i(123) {}
//		int i;
//	};
//}





class DCT_color_rgba_f
{
	/*
	this color class is designed to do some complex calculating. Some in rgb space, some in hsv space, some in other space.
	some fomular are from https://www.easyrgb.com/en/
	*/
public:
	//build in ctor
	DCT_color_rgba_f();
	DCT_color_rgba_f(const DCT_color_rgba_f&);
	DCT_color_rgba_f(DCT_color_rgba_f&&);

	//customized ctor
	DCT_color_rgba_f(float r,  float g,  float b,  float a = 1.f);

	//should this be private? not very sure.
	//dtor
	virtual ~DCT_color_rgba_f();

	//operator overload
	DCT_color_rgba_f& operator=(const DCT_color_rgba_f&);
	DCT_color_rgba_f& operator=(DCT_color_rgba_f&&);
	DCT_color_rgba_f operator+(const DCT_color_rgba_f& other);
	DCT_color_rgba_f operator-(const DCT_color_rgba_f& other);

	//gray scale
	void set_to_gray_01(const float src = 0.5f, const float in_a = 1.f);
	static DCT_color_rgba_f make_gray(const float src = 0.5f, const float in_a = 1.f);
	//特殊gets sets
	//?????????
	//计算，混合那些还没加

	//blending
	DCT_color_rgba_f& overlapped_by(const DCT_color_rgba_f& upper);
	//不慌DCT_color_rgba_f& rgb_lerp(const DCT_color_rgba_f& upper);//Linear interpolation

protected:
	//inner helper tool
	static float clamp_to_0_1(const float);

	//data members
protected:
	float r, g, b, a;
	//gets sets
public:
	float getr()const;
	float getg()const;
	float getb()const;
	float geta()const;
	void setr(const float);
	void setg(const float);
	void setb(const float);
	void seta(const float);



};







