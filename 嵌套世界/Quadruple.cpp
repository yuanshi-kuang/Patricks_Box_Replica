#pragma once
template<typename A, typename B, typename C, typename D>
class Quadruple 
{
public:
    A one;
    B two;
    C three;
    D four;
    Quadruple():one(),two(),three(),four() {}
    Quadruple(const A& a, const B& b, const C& c, const D& d) : one(a), two(b), three(c), four(d) {}
};