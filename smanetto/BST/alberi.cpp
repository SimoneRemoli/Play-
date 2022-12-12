#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <math.h>
using namespace std;
#define M 10


struct NODO
{
	int k;
	NODO *p_DX;
	NODO *p_SX;
};
void insert(NODO*&,int);
void pre_order_visit(NODO*&);
void post_order_visit(NODO*&);
void in_order_visit(NODO*&);

int main()
{
	int max = 0,app;

	NODO *root;
	root = new NODO;
	root->k=0;
	root->p_DX=NULL;
	root->p_SX=NULL;
	cout<<" Nodo radice --> "<<root->k<<endl;
	srand((unsigned)time(NULL));
	for(int i=0;i<M;i++)
	{
		app = rand()%100+1;
		if(app%2==0)
		{
			cout<<"SX"<<"\t";
			insert(root->p_SX,app);
		}
		else
		{
			cout<<"DX"<<"\t";
			insert(root->p_DX,app);
		}
	}
	cout<<" View PRE_ORDER . . . "<<endl;
	pre_order_visit(root);
	cout<<" View POST_ORDER . . . "<<endl;
	post_order_visit(root);
	cout<<" View IN_ORDER . . . "<<endl;
	in_order_visit(root);
	return 0;
}
void insert(NODO *&root,int val)
{
	if(root==NULL)
	{
		root=new NODO;
		root->p_DX=NULL;
		root->p_SX=NULL;
		root->k=val;
		cout<<val<<endl;
	}
	else
		if(val>root->k)
		{
			cout<<"SX(1)"<<"\t";
			insert(root->p_SX,val);
		}
		else
		{
			cout<<"DX(1)"<<"\t";
			insert(root->p_DX,val);
		}
}
void pre_order_visit(NODO *&root)
{
	if(root == NULL)
		return;
	else
	{
		cout<<root->k<<endl;
		pre_order_visit(root->p_DX);
		pre_order_visit(root->p_SX);
	}
}
void post_order_visit(NODO *&root)
{
	if(root == NULL)
		return;
	else
	{
		post_order_visit(root->p_SX);
		post_order_visit(root->p_DX);
		cout<<root->k<<endl;
	}
}
void in_order_visit(NODO *&root)
{
	if(root == NULL)
		return;
	else
	{
		in_order_visit(root->p_SX);
		cout<<root->k<<endl;
		in_order_visit(root->p_DX);
	}
}
