#include "../inc/DCT color.h"


//build in ctor
DCT_color_rgba_f::DCT_color_rgba_f() { r = 0.f; g = 0.f; b = 0.f; a = 1.f; };
DCT_color_rgba_f::DCT_color_rgba_f(const DCT_color_rgba_f& in) { r = in.r; g = in.g; b = in.b; a = in.a; };
DCT_color_rgba_f::DCT_color_rgba_f(DCT_color_rgba_f&& in) { r = in.r; g = in.g; b = in.b; a = in.a; };//not very optimized?

//customized ctor
DCT_color_rgba_f::DCT_color_rgba_f( float  in_r,  float  in_g,  float  in_b,  float  in_a)
{
	r = in_r;
	g = in_g;
	b = in_b;
	a = in_a;
}

//dtor
DCT_color_rgba_f::~DCT_color_rgba_f() {};//not very sure whether this one has to be virtual.

//operator overload
DCT_color_rgba_f& DCT_color_rgba_f::operator=(const DCT_color_rgba_f&in) 
{
	r = in.r; g = in.g; b = in.b; a = in.a;
	return *this;
};
DCT_color_rgba_f& DCT_color_rgba_f::operator=(DCT_color_rgba_f&&in)
{
	r = in.r; g = in.g; b = in.b; a = in.a;
	return *this;
};
DCT_color_rgba_f DCT_color_rgba_f::operator+(const DCT_color_rgba_f & other)
{//add by rgb and linear.
	return DCT_color_rgba_f(this->r + other.r, this->g + other.g, this->b + other.b);
}
DCT_color_rgba_f DCT_color_rgba_f::operator-(const DCT_color_rgba_f & other)
{//add by rgb and linear.
	return DCT_color_rgba_f(this->r - other.r, this->g - other.g, this->b - other.b);
}

//gray scale
void DCT_color_rgba_f::set_to_gray_01(const float src, const float in_a)
{
	r = g = b = clamp_to_0_1(src); a = clamp_to_0_1(in_a);
}
DCT_color_rgba_f DCT_color_rgba_f::make_gray(const float src, const float in_a)
{
	float temp(clamp_to_0_1(src));
	return DCT_color_rgba_f(temp, temp, temp, clamp_to_0_1(in_a));
}

//blending
DCT_color_rgba_f& DCT_color_rgba_f::overlapped_by(const DCT_color_rgba_f& upper)
{
	float lower_a_mul_one_minus__upper_a = a*(1.f - upper.a);
	r = lower_a_mul_one_minus__upper_a * r + upper.a*upper.r;
	g = lower_a_mul_one_minus__upper_a * g + upper.a*upper.g;
	b = lower_a_mul_one_minus__upper_a * b + upper.a*upper.b;
	a = lower_a_mul_one_minus__upper_a + upper.a;
	return *this;
}

//inner helper tool
float DCT_color_rgba_f::clamp_to_0_1(const float ref) 
{
	float result = ref;
	if (ref < 0.f)result = 0.f;
	else if (ref > 1.0f)result = 1.0f;
	else if (!(ref >= 0.f && ref <= 1.0f)) result = 0.f;//for nan
	return result;
}

//gets sets
float DCT_color_rgba_f::getr() const { return clamp_to_0_1(this->r);}
float DCT_color_rgba_f::getg() const { return clamp_to_0_1(this->g); }
float DCT_color_rgba_f::getb() const { return clamp_to_0_1(this->b); }
float DCT_color_rgba_f::geta() const { return clamp_to_0_1(this->a); }
void DCT_color_rgba_f::setr(const float in) { r = in; clamp_to_0_1(r); }
void DCT_color_rgba_f::setg(const float in) { g = in; clamp_to_0_1(g); }
void DCT_color_rgba_f::setb(const float in) { b = in; clamp_to_0_1(b); }
void DCT_color_rgba_f::seta(const float in) { a = in; clamp_to_0_1(a); }






