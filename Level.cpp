#include "Level.h"
void Level::move(const int& x, const int& y, const Direction& dir)
{
	if (havep)
	{
		Block* worddata = &word[pats.w];//�ؿ�
		BlockElement* wordpbedata = word[pats.w].maps(pats.z, pats.y, pats.x); //patλ�õ�Ԫ��
		BlockElement* getnext = word[pats.w].maps(pats.z, pats.y + y, pats.x + x);//getnext
		if (getnext->push)
		{
			//��������
			XYZ eye = { pats.x,pats.y,pats.z };//�۲�λ��
			int iterate = 0;//��������
			BlockElement* data = nullptr;//��������
			eye.add(x, y);//ƫ��
			iterate++;//��������

			//��ǰ����
			while (true)
			{
				data = word[pats.w].maps(eye.z, eye.y, eye.x);
				if (data->push && data->name != null) 
				{
					eye.add(x, y); 
					iterate++; 
					continue; 
				}
				else if (!data->push) 
				{
					direction = dir; 
					return; 
				}
				else if (data->name == null) 
				{
					iterate--; 
					break; 
				}
			}

			//ִ���ƶ�
			for (int i = iterate; i >= 0; i--)
			{
				//State name = worddata->maps(pats.z, pats.y + y * i, pats.x + x * i)->name;
				//worddata->maps(pats.z, pats.y + y * i, pats.x + x * i)->del();
				//*worddata->maps(pats.z, pats.y + y * (i + 1), pats.x + x * (i + 1)) = name;
				*worddata->maps(pats.z, pats.y + y * (i + 1), pats.x + x * (i + 1)) = worddata->maps(pats.z, pats.y + y * i, pats.x + x * i)->name;
				worddata->maps(pats.z, pats.y + y * i, pats.x + x * i)->del();
			}
			pats.x += x;//�������λ��
			pats.y += y;
			direction = dir;//������ҷ���
			
			//ʤ���ж�
			if (pexitend.w != -1 || !bexitend.empty())
			{
				bool pwin = false;
				bool bwin = false;
				if (pexitend.w != -1)
				{
					BlockElement* pdata = word[pexitend.w].maps(pexitend.z + 1, pexitend.y, pexitend.x);
					if (pdata->name == player) 
					{
						pwin = true; 
					}
				}
				if (!bexitend.empty())
				{
					int boxwin = 0;
					for (const auto& deta : bexitend)
					{
						BlockElement* bdata = word[deta.w].maps(deta.z + 1, deta.y, deta.x);
						if (bdata->name == box) 
						{
							boxwin++; 
						}
					}
					bwin = (boxwin == bexitend.size());
				}
				//������pexit��bexitͬʱû�е����
				//00 00 error
				//10 00 false
				//11 00 true //�ж����pexitend.w == -1����
				//10 10 false
				//11 11 true
				if ((pexitend.w != -1 && pwin || pexitend.w == -1) && (!bexitend.empty() && bwin || bexitend.empty())) 
				{
					victory = true; 
				}
			}
		}
		else 
		{
			direction = dir; 
		}
	}
}
void Level::addblock(const string& str)
{
	word.push_back(str);
	//��������յ�
	if (word.back().pexitend != nullptr)
	{
		XYZ* location = &word.back().pexitend->Location;
		pexitend = { int(word.size()) - 1, location->x, location->y, location->z };
	}
	//�����������磬�������������յ㡣
	for (BlockElement* data : word.back().bexitend)
	{
		if (data != nullptr)
		{
			bexitend.push_back({ int(word.size()) - 1, data->Location.x, data->Location.y, data->Location.z });
		}
	}
	//����patsλ��
	if (word.back().havep)
	{
		havep = true;
		pats = word.back().pat->Location;
	}
}
void Level::up() 
{
	move(0, -1, Direction::up); 
}
void Level::down() 
{
	move(0, 1, Direction::down); 
}
void Level::left() 
{
	move(-1, 0, Direction::left); 
}
void Level::right() 
{
	move(1, 0, Direction::right); 
}
