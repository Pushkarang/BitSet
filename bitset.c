#include<stdio.h>
#include<stdlib.h>
struct node
{
	int i;// index od node
	int s;// int to store 32 consecutive numbers starting from index i
	struct node *next;
};


struct node* insert(struct node *h,int data)
{
	int index=(int)((data/32)*32);
	struct node *H;

	if(h==NULL)
	{
		h=(struct node*)malloc(sizeof(struct node));
		h->i=index;
		h->s|=1<<(data%32);
		h->next=NULL;
		return h;
	}
	struct node *p;
	p=h;
	H=h;
	while(h!=NULL)
	{
		if(h->i==index)
		{
			h->s|=1<<(data%32);
			return H;
		}

		else if(h->i >index)
		{
			struct node *temp;
			temp=(struct node*)malloc(sizeof(struct node));
			temp->i=index;
			temp->s|=1<<(data%32);
			p->next=temp;
			temp->next=h;
			return H;
		}
		else if(h->i < index)
		{
			p=h;
			int l;
			l=h->i;
			h=h->next;
		}
		else
		{
			struct node *temp;
			temp=(struct node*)malloc(sizeof(struct node));
			temp->i=index;
			temp->s|=1<<(data%32);
			p->next=temp;
			temp->next=NULL;
			return H;
		}
	}
	struct node *temp;
	temp=(struct node*)malloc(sizeof(struct node));
	temp->i=index;
	temp->s|=1<<(data%32);
	p->next=temp;
	temp->next=NULL;
	return H;
}


void display(struct node *h)
{
	int i,a;
	printf("Set {");
	while(h!=NULL)
	{
		int x=h->i;
		a=h->s;
		for(i=x;i<x+32;i++)
		{
			if(a>>i & 0x1)
			{
				printf(",'%d'",i);
			}
		}
		h=h->next;
	}
	printf("}\n");
}


struct node* uni(struct node *A,struct node *B,struct node *C)
{
	int a,x,i;
	while(A!=NULL)
	{
		a=A->s;
		x=A->i;
		for(i=x;i<x+32;i++)
		{
			if(a>>i & 0x1)
			{
				C=insert(C,i);
			}
		}
		A=A->next;
	}
	while(B!=NULL)
	{
		a=B->s;
		x=B->i;
		for(i=x;i<x+32;i++)
		{
			if(a>>i & 0x1)
			{
				C=insert(C,i);
			}
		}
		B=B->next;
	}
	return C;
}


struct node* inter(struct node *A,struct node *B,struct node *C)
{
	int a,x,i;
	while(A!=NULL && B!=NULL)
	{
		if(A->i==B->i)
		{
			int o,p;
			o=A->s;
			p=B->s;
			a= o & p;
			x=A->i;
			for(i=x;i<x+32;i++)
			{
				if(a>>i & 0x1)
				{

					C=insert(C,i);
				}
			}
			A=A->next;
			B=B->next;
			continue;
		}

		else if(A->i<B->i){A=A->next;continue;}
		else
		{
			A=A->next;
			B=B->next;
		}
	}
	return C;

}


struct node* AsubB(struct node *A,struct node *B,struct node *C)
{
	int a,x,i;
	while(A!=NULL && B!=NULL)
	{
		if(A->i==B->i)
		{
			int o,p;
			o=A->s;
			p=B->s;
			a= o^p;
			a=a&o;
			x=A->i;
			for(i=x;i<x+32;i++)
			{
				if(a>>i & 0x1)
				{

					C=insert(C,i);
				}
			}
			A=A->next;
			B=B->next;
			continue;
		}
		if(A!=NULL && B!=NULL)
		{
			if(A->i<B->i)
			{
				a=A->s;
				x=A->i;
				for(i=x;i<x+32;i++)
				{
					if(a>>i & 0x1)
					{

						C=insert(C,i);
					}
				}
				A=A->next;
				continue;
			}
		}

	}
	return C;

}


struct node* BsubA(struct node *A,struct node *B,struct node *C)
{
	C=AsubB(B,A,C);
	return C;
}

struct node* Set(struct node *a){
	a=insert(a,0);
	a->s=a->s&0x0;
	return a;
}


void main()
{
	struct node *h,*j,*k;
	h=NULL;
	j=NULL;
	k=NULL;
	k=Set(k);
	h=Set(h);
	j=Set(j);
	int jj,rad;
	for(jj=0;jj<10;jj++){
	h=insert(h,jj);
	k=insert(k,jj+5);
	}
	printf("This is set 1 =");
	display(h);
	printf("This is set 2 =");
	display(k);
	j=uni(h,k,j);
	printf("Union of set 1 and set 2 =");
	display(j);
	j=NULL;
	printf("Intersection of set 1 and set 2 =");
	j=inter(h,k,j);
	display(j);
	j=NULL;
	printf("set 1 - set 2 =");
	j=AsubB(h,k,j);
	display(j);
	j=NULL;
	printf("set 2 - set 1 =");
	j=BsubA(h,k,j);
	display(j);
	j=NULL;
	
	
}
