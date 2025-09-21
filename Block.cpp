#include "Block.h"
void Block::loading_a(const string & code)
{
	//�ַ�����
	int data = 0;
	//��ʼ��ÿ��Ԫ��
	for (int i = 0; i < mapsize.z; i++)
	{
		for (int j = 0; j < mapsize.y; j++)
		{
			for (int k = 0; k < mapsize.x; k++)
			{
				//���õ�ͼ������������������
				if (j == 0 && k == 0) { data = 0; }
				if (code[data] == '\n') { data++; }
				//��0���޸�Ϊ����
				if (i == 0)
				{
					*maps(i, j, k) = flor;
					maps(i, j, k)->Location = { k,j,i };
				}
				//��1,2�㰴�յ�ͼ������и��¡�
				else if (i == 1)
				{
					switch (code[data])
					{
					case '\n':break;
					case '0':break;
					case '1':break;
					case '2':break;
					case '3':break;
					case '4':break;
					case '5':*maps(i, j, k) = pexit; pexitend = maps(i, j, k);          break;
					case '6':*maps(i, j, k) = bexit; bexitend.push_back(maps(i, j, k)); break;
					default:break;
					}
					maps(i, j, k)->Location = { k,j,i };
					data++;
				}
				else if (i == 2)
				{
					switch (code[data])
					{
					case '\n':break;
					case '0':*maps(i, j, k) = null;   break;
					case '1':*maps(i, j, k) = flor;   break;
					case '2':*maps(i, j, k) = player; havep = true; pat = maps(i, j, k); break;
					case '3':*maps(i, j, k) = box;    break;
					case '4':*maps(i, j, k) = wall;   break;
					case '5':break;
					case '6':break;
					default:break;
					}
					maps(i, j, k)->Location = { k,j,i };
					data++;
				}
			}
		}
	}
}
void Block::loading_b(const string& code)
{
	//�ַ�����
	int data = 0;
	//��ʼ��ÿ��Ԫ��
	for (int i = 0; i < mapsize.z; i++)
	{
		for (int j = 0; j < mapsize.y; j++)
		{
			for (int k = 0; k < mapsize.x; k++)
			{
				//���õ�ͼ������������������
				if (j == 0 && k == 0) { data = 0; }
				if (code[data] == '\n') { data++; }
				//��0��
				if (i == 0)
				{
					*maps(i, j, k) = flor;
					maps(i, j, k)->Location = { k,j,i };
				}
				//��1��
				else if (i == 1)
				{
					switch (code[data])
					{
					case '\n':break;
					case '0':*maps(i, j, k) = null;   break;
					case '1':*maps(i, j, k) = flor;   break;
					case '2':*maps(i, j, k) = player; break;
					case '3':*maps(i, j, k) = box;    break;
					case '4':*maps(i, j, k) = wall;   break;
					case '5':*maps(i, j, k) = pexit; pexitend = maps(i, j, k);          break;
					case '6':*maps(i, j, k) = bexit; bexitend.push_back(maps(i, j, k)); break;
					default:break;
					}
					maps(i, j, k)->Location = { k,j,i };
					data++;
				}
				//��2��
				else if (i == 2)
				{
					if (j == 0 && k == 0) { data = 0; }
					if (code[data] == '\n') { data++; }
					switch (code[data])
					{
					case '\n':break;
					case '0':*maps(i, j, k) = null;   break;
					case '1':*maps(i, j, k) = flor;   break;
					case '2':*maps(i, j, k) = player; havep = true; pat = maps(i, j, k); break;
					case '3':*maps(i, j, k) = box;    break;
					case '4':*maps(i, j, k) = wall;   break;
					case '5':*maps(i, j, k) = pexit;  break;
					case '6':*maps(i, j, k) = bexit;  break;
					default:break;
					}
					maps(i, j, k)->Location = { k,j,i };
					data++;
				}
			}
		}
	}
}
void Block::loading_c(const string& code)
{
	//�ַ�����
	int data = 0;
	//��ʼ��ÿ��Ԫ��
	for (int i = 0; i < mapsize.z; i++)
	{
		for (int j = 0; j < mapsize.y; j++)
		{
			for (int k = 0; k < mapsize.x; k++)
			{
				//���õ�ͼ������������������
				if (j == 0 && k == 0) { data = 0; }
				if (code[data] == '\n') { data++; }
				//��0��
				if (i == 0)
				{
					switch (code[data])
					{
					case '\n':break;
					case '0':*maps(i, j, k) = null;   break;
					case '1':*maps(i, j, k) = flor;   break;
					case '2':*maps(i, j, k) = player; break;
					case '3':*maps(i, j, k) = box;    break;
					case '4':*maps(i, j, k) = wall;   break;
					case '5':*maps(i, j, k) = pexit;  break;
					case '6':*maps(i, j, k) = bexit;  break;
					default:break;
					}
					maps(i, j, k)->Location = { k,j,i };
					data++;
				}
				//��1��
				else if (i == 1)
				{
					switch (code[data])
					{
					case '\n':break;
					case '0':*maps(i, j, k) = null;   break;
					case '1':*maps(i, j, k) = flor;   break;
					case '2':*maps(i, j, k) = player; break;
					case '3':*maps(i, j, k) = box;    break;
					case '4':*maps(i, j, k) = wall;   break;
					case '5':*maps(i, j, k) = pexit; pexitend = maps(i, j, k);          break;
					case '6':*maps(i, j, k) = bexit; bexitend.push_back(maps(i, j, k)); break;
					default:break;
					}
					maps(i, j, k)->Location = { k,j,i };
					data++;
				}
				//��2��
				else if (i == 2)
				{
					if (j == 0 && k == 0) { data = 0; }
					if (code[data] == '\n') { data++; }
					switch (code[data])
					{
					case '\n':break;
					case '0':*maps(i, j, k) = null;   break;
					case '1':*maps(i, j, k) = flor;   break;
					case '2':*maps(i, j, k) = player; havep = true; pat = maps(i, j, k); break;
					case '3':*maps(i, j, k) = box;    break;
					case '4':*maps(i, j, k) = wall;   break;
					case '5':*maps(i, j, k) = pexit;  break;
					case '6':*maps(i, j, k) = bexit;  break;
					default:break;
					}
					maps(i, j, k)->Location = { k,j,i };
					data++;
				}
			}
		}
	}
}
BlockElement* Block::maps(const int& z, const int& y, const int& x) 
{
	return &map[z * (mapsize.y * mapsize.x) + y * mapsize.x + x]; 
}
