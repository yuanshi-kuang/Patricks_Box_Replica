
#include "BlockElement.h"
#include "Tree.h"



State BlockElement::Compatible(string code) 
{
    if (code == "null") { return null; }
    else if (code == "flor") { return flor; }
    else if (code == "player") { return player; }
    else if (code == "box") { return box; }
    else if (code == "wall") { return wall; }
    else if (code == "pexit") { return pexit; }
    else if (code == "bexit") { return bexit; }
    else if (code == "word") { return word; }
    else { return null; }
};
BlockElement::BlockElement(State Element) { load(Element); }
BlockElement::BlockElement(const string Element) { load(Compatible(Element)); }
BlockElement::BlockElement(const State& name, const bool& push) : name(name), push(push) {}
BlockElement::BlockElement(const BlockElement& data) 
{
    name = data.name;
    push = data.push;
    son = data.son;
}
BlockElement& BlockElement::operator=(const BlockElement& data) 
{
    name = data.name;
    push = data.push;
    son = data.son;
    return *this;
}
void BlockElement::load(State Element, int son )
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
    case word:  push = true;  break;
    default:break;
    }
    //if (name == word && son != -1) { this->son = Tree::pairid(son); }
}
void BlockElement::del() { *this = BlockElement("null"); }


