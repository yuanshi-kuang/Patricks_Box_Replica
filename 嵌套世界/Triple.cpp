#pragma once
template<typename A, typename B, typename C>
class Triple 
{
public:
    A one;
    B two;
    C three;
    Triple(const A& a, const B& b, const C& c) : one(a), two(b), three(c) {}
};