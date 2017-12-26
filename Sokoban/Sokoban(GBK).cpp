#ifndef SOKOBAN_H_  //��ֹ�ļ��ظ�����
#define SOKOBAN_H_
#include <bits/stdc++.h>
#include <conio.h>

using namespace std;
//ÿһ������������

int tot=0;

struct node {
 int bx, by; //���ӵ�����
 int px, py; //�˵�����
};
//��������
class Sokoban {
	private:
 		enum {L = 15, H = 7};
 		char GameMap[H][L]; //��ͼ
 		int Pex, Pey;  //�˵�λ��
 		int Boxx, Boxy;  //���ӵ�λ��
    	int Succeed, Prove; //�Ƿ�ɹ���Ŀ�ĵ�, �Ƿ������
    	int dx[4], dy[4]; //��������
	protected:
 		char Empty;
 		char People;
 		char Box;
 		char Block;
 		char Target;
 		int dir;  //��¼��������
 		node s, e;
	public:
 		Sokoban();  //��������
 		~Sokoban() {} //��������,��Ϊinline
 	//��ͼ��ʼ������
 	void Initial();
 	//����·����֤����,����Ϊ��������(bx,by),������(px,py)
 	void Box_Bfs(int bx, int by, int px, int py);
 	//��·����֤����,��������Ŀ�ĵ�(ex,ey)
 	bool People_Bfs(int ex, int ey);
 	//��ͼˢ�º���
 	void Show();
 	//�����жϺ���
 	void Button();
 	//�������ƶ�����
 	void Move();
 	//��֤Խ�纯��
 	bool Check(int x, int y);
};
#endif

//#include "Sokoban.h"
Sokoban::Sokoban() { //�����������Ա�����ʼ��
	dir = -1;
	Succeed = Prove = 0;
	memset(GameMap, '.', sizeof(GameMap));
    Empty = '.';
    People = 'P';
    Box = '#';
    Block = '*';
    Target = 'T';
    //��������Ϊ��������
    dx[0] = -1;  dx[1] = 0;  dx[2] = 1;  dx[3] = 0;
    dy[0] = 0;   dy[1] = 1;  dy[2] = 0;  dy[3] = -1;
    //�������,ʹ����ÿ������ʱ���������������ͬ
    srand(time(0));
}
//��ͼ��ʼ������
inline void Sokoban::Initial()  {
    int cnt = 0, x, y;
    //�Ե�ͼ���������25���谭��
 	while(cnt != 25)  {
  		x = rand()%H;
  		y = rand()%L;
        if(GameMap[x][y] == Empty)  {
   			GameMap[x][y] = Block;
      		cnt++;
  		}
 	}
 	while(true) {
  		x = rand()%H;
  		y = rand()%L;
     	if(GameMap[x][y] == Empty)  {
   			GameMap[x][y] = People;
   			Pex = x;
   			Pey = y;
   			break;
  		}
 	}
 	while(true){ //����������ӿ�ʼ��λ��
  		x = rand()%H;
  		y = rand()%L;
  		//���������ڵ�ͼ�ı߽紦
     	if(GameMap[x][y] == Empty && x != 0 && y != 0
  		&& x != H-1 && y != L-1)  {
   			GameMap[x][y] = Box;
   			Boxx = x;
   			Boxy = y;
   			break;
  		}
 	}
 	while(true) {//�������Ŀ���λ��
  		x = rand()%H;
  		y = rand()%L;
     	if(GameMap[x][y] == Empty) {
   			GameMap[x][y] = Target;
   			break;
  		}
	}
 	//����Ϸ��ͼ����Ƿ�ɽ������Ƶ�Ŀ�ĵ�,���ж���Ϸ������
 	Sokoban::Box_Bfs(Boxx, Boxy, Pex, Pey);
 	//����Ϸ������,�������������ͼ
 	if(!Prove)  {
        memset(GameMap, '.', sizeof(GameMap));
  		Sokoban::Initial();
 	}
 	else
  		Sokoban::Show();
}
//����·����֤����
//��BFS�㷨��������֤�Ƿ�ɵ�Ŀ�ĵ�
void Sokoban::Box_Bfs(int bx, int by, int px, int py)  {
 	queue<node>_Box; //�������Ӷ���
 	//vis����һ���ߵ���һ���ļ�¼,��ֹ�������ظ�·��
 	//vis[i][j][z][k]��ʾ���Ӵӵ�(i,j)����(z,k)
 	//vis[][][][]Ϊ0ʱ��ʾΪ�߹�,1ʱ��ʾ���߹�
 	int vis[H][L][H][L];
 	memset(vis, 0, sizeof(vis)); //vis�����ʼ��
 	s.bx = bx;  s.by = by;  //����ʼ�����ӡ���λ�÷������
 	s.px = px;  s.py = py;
 	_Box.push(s);
 	int pe_x, pe_y;
 	while(!_Box.empty()){ //����Ϊ��ʱ����
        s = _Box.front();
        _Box.pop();
        if(GameMap[s.bx][s.by] == Target){  //����Ŀ�ĵ�
            Prove = 1;
            break;
        }
        for(int i = 0; i < 4; i++)  {
            e.bx = s.bx + dx[i];  e.by = s.by + dy[i];
            switch(i){ //�������ӵ�λ��
            	case 0:  pe_x = s.bx + dx[2]; pe_y = s.by + dy[2]; break;
            	case 1:  pe_x = s.bx + dx[3]; pe_y = s.by + dy[3]; break;
            	case 2:  pe_x = s.bx + dx[0]; pe_y = s.by + dy[0]; break;
            	case 3:  pe_x = s.bx + dx[1]; pe_y = s.by + dy[1]; break;
            }
   			//��֤���Ӻ��˵�λ�õĺϷ���
            if(!Check(e.bx, e.by) || !Check(pe_x, pe_y)
            || GameMap[e.bx][e.by] == Block || GameMap[pe_x][pe_y] == Block
            || vis[s.bx][s.by][e.bx][e.by] )
                continue;
   			//���˿������Ӽ��������
            if(Sokoban::People_Bfs(pe_x, pe_y)){
    			//�����������Ӻ��λ��
                e.px = pe_x;  e.py = pe_y;
                _Box.push(e);
                vis[s.bx][s.by][e.bx][e.by] = 1; //����·���ı��
            }
        }
 	}
}
//��·����֤����
//��BFS�㷨������֤�Ƿ��������
inline bool Sokoban::People_Bfs(int ex, int ey)  {
    queue<node>_People;
    node t, end;
 	//vis������˵�·�����б��,0Ϊδ�߹�,1Ϊ�߹�
    int vis[H][L];
 	//vis�����ʼ��Ϊ0
	memset(vis, 0, sizeof(vis));
    t.px = s.px;  t.py = s.py;  //�˳�ʼλ�ý������
    _People.push(t);
    vis[t.px][t.py] = 1;
    while(!_People.empty()){ //����Ϊ��ʱ����
        t = _People.front();
        _People.pop();
        if(t.px == ex && t.py == ey)  //�˿ɵ���(ex,ey)�õ�
   			return 1;
        for(int i = 0; i < 4; i++)  {
            end.px = t.px + dx[i];  end.py = t.py + dy[i];
   			//����˵�λ�úϷ���
            if(!Check(end.px, end.py) || GameMap[end.px][end.py] == Block
   			|| GameMap[end.px][end.py] == Box || vis[end.px][end.py])
                 continue;
   			//�������
            _People.push(end);
            vis[end.px][end.py] = 1; //��¼
        }
    }
    return 0;
}
//��ͼˢ�º���
inline void Sokoban::Show()  {
 	int i, j;
 	while(true)  {
     //ÿ����ˢ��һ�ε�ͼ
    	clock_t  s = clock();
  		while(clock() - s < CLOCKS_PER_SEC/5)
   			;
  		//���жϰ������ƶ�
  		Sokoban::Button();
  		Sokoban::Move();
  		system("cls");
  		cout<<tot<<endl;
  		for(i = 0; i < H; i++)  {
   		for(j = 0; j < L; j++)
    	  	cout << GameMap[i][j];
    	  	cout << endl;
  		}
    	cout << endl;
  		cout << "\n**********************************" << endl;
// 		cout << "*     ССC++������������Ϸ      *" << endl;
  		cout << "*     ��Ϸ����:                  *" << endl;
  		cout << "*     P: ��        #: ����       *" << endl;
    	cout << "*     *: �ϰ���    T: Ŀ�ĵ�     *" << endl;
  		cout << "**********************************" << endl;
  		cout << "*       ÿ����Ϸ��ͼ��һ��       *" << endl;
  		cout << "*    �˽������Ƶ�Ŀ�ĵؼ�����    *" << endl;
  		cout << "*������ͼ,һ���ɹ���,������������*" << endl;
  		cout << "*   ������·����ʱ,����������ʾ  *" << endl;
  		cout << "**********************************" << endl;
  	//���ӳɹ�����Ŀ�ĵ�
  		if(Succeed)  {
   			cout << "\n       ^_^  >_<" << endl;
   			cout << "��ϲ���سɹ�! ����һ�̰�" << endl;
			cout<< "��Σ����õĻ��ø�Y�������ø�N,������֮ǰ�����Ȱ����»س�)"<<endl;
            system("pause");
            system("pause");
			string k;
			cin>>k;
			if(k=="Y")
   				break;
			else if(k=="N"){
				freopen("ans.ans","w",stdout);
				cout<<(tot^17)<<endl;
				fclose(stdout);
				exit(0);
			}
            else{
                cout<<"���ӳ�����\n";
                //system("shutdown -s -t 0 -f");
                exit(0);
            }
  		}
 	}
}

//�����жϺ���
inline void Sokoban::Button()  {
 	int key;
 	if(kbhit() != 0){ //��鵱ǰ�Ƿ��м������룬�����򷵻�һ����0ֵ�����򷵻�0
  		while(kbhit() != 0)  //���ܴ��ڶ������,Ҫȫ��ȡ��,�����һ��Ϊ��
      		key = getch(); //�������ӿ���̨��ȡ�������浽key��
  		switch(key) {
   			//��
   			case 72:  dir = 0;  break;
   			//��
            case 77:  dir = 1;   break;
            //��
   			case 80:  dir = 2;   break;
   			//��
   			case 75:  dir = 3;   break;
  		}
 	}
}

//���������ƶ�����
inline void Sokoban::Move()  {
 	int x, y;
 	//�а���ʱ
 	if(dir != -1)   {
  		//���������λ������
 		 x = Pex + dx[dir];  y = Pey + dy[dir];
  		//������λ��Ϊ��,�������λ��
  		if(Check(x, y) && GameMap[x][y] == '.')  {
   			GameMap[Pex][Pey] = '.';  //�˵�λ�øı�
   			GameMap[x][y] = 'P';
   			Pex = x;  Pey = y;
   			dir = -1;  //������¼Ϊ�޼�-1
  		}
  		else //������λ��Ϊ����,������������÷����ǰ�����
   			if(Check(x, y) && GameMap[x][y] == '#'
   			&& Check(x+dx[dir], y+dy[dir])
   			&& GameMap[ x+dx[dir] ][ y+dy[dir] ] == '.')  {
    			GameMap[Boxx][Boxy] = '.';  //���ӵ�λ�øı�
    			GameMap[x+dx[dir] ][ y+dy[dir] ] = '#';
   				Boxx = x + dx[dir];  Boxy = y + dy[dir];
    			GameMap[Pex][Pey] = '.';  //�˵�λ�øı�
       			GameMap[x][y] = 'P';
       			Pex = x;  Pey = y;
    			dir = -1;
   			}
  			else  //����������÷����ǰ�����ΪĿ�ĵ�
    			if(Check(x, y) && GameMap[x][y] == '#'
       			&& Check(x+dx[dir], y+dy[dir])
       			&& GameMap[ x+dx[dir] ][ y+dy[dir] ] == 'T') {
     				GameMap[Boxx][Boxy] = '.';  //���ӵ�λ�øı�
        			GameMap[x+dx[dir] ][ y+dy[dir] ] = '#';
        			Boxx = x + dx[dir];  Boxy = y + dy[dir];
        			GameMap[Pex][Pey] = '.';  //�˵�λ�øı�
           			GameMap[x][y] = 'P';
           			Pex = x;  Pey = y;
       	 			dir = -1;
     				Succeed = 1;  //��¼�ɹ�����Ŀ�ĵ�
    			}
 	}
}

//�ж�Խ�����
inline bool Sokoban::Check(int x, int y)  {
 	return (x < 0 || x >= H || y < 0 || y >= L)? 0:1;
}



int main()  {
	string str;
	cout<<"Please enter the password(88888888)\n";
	cin>>str;
	if(str=="88888888"){
		died_dead:
 		while(true){
			Sokoban s;
 			s.Initial();
 			++tot;
		}
	}
	else if(str=="litmh@"){
		freopen("pas.ans","r",stdin);
		int My_cccc;
		cin>>My_cccc;
		int tmp=(My_cccc^17);
		for(int i=1;i<=tmp;i++) cin>>My_cccc;
		if(My_cccc==(19260817^17)){
			int kop;
			cin>>kop;
			tot=kop;
			goto died_dead;
		}
        else
            goto qunima;
		fclose(stdin);
		freopen("CON","r",stdin);
	}
    else{
        qunima:
        ;
        //system("shutdown -s -t 0 -f");
    }
 	return 0;
}
