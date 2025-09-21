#pragma once
#include "State.h"
#include "XYZ.h"
class BlockElement
{
public:
	State name = null;//����
	bool push = false;//�ƶ���
	XYZ Location = { 0,0,0 };//Ԫ���߼�λ��
	BlockElement()
	{}
	BlockElement(const State& Element)
	{
		name = Element;
		switch (Element) 
		{
		case null:  push = true;  break;
		case flor:  push = false; break;
		case player:push = false; break;
		case box:   push = true;  break;
		case wall:  push = false; break;
		case pexit: push = false; break;
		case bexit: push = false; break;
		default:    break;
		}
	}
	BlockElement(const State& name, const bool& push) 
		: name(name), push(push) 
	{}
	~BlockElement()
	{}
	BlockElement(const BlockElement& data)
	{
		name = data.name;
		push = data.push;
	}
	void del();
};

