/*
 * List.h
 *
 *  Created on: Aug 1, 2018
 *      Author: OS1
 */

#ifndef LIST_H_
#define LIST_H_

template <class T> class List
{
private:
	struct Element
	{
		T Member;
		Element * next;
	};

	Element * first,*last,*iterrator;

	unsigned int numOfMembers;
public:




	List (): first(0),last(0),iterrator(0),numOfMembers(0){}

	void add (T nMember )
	{
		Element * nElement= new Element();
		nElement->Member=nMember;
		nElement->next=0;
		if(first==0)
		{
			last=first=nElement;
		}
		else
		{
			last=last->next=nElement;
		}
		numOfMembers++;
	}

	T remove ()
	{
		if(first==0)return 0;
		else
		{
			Element* pom= first;
			T ret;
			if(last==first)last=0;
			first=first->next;
			ret=pom->Member;
			delete pom;
			numOfMembers--;
			return ret;
		}
	}

	T removeAt (unsigned int i)
	{
		Element * pom=first,*befpom=0;
		T ret=0;
		for(unsigned j=0;j<i;j++)
		{
			befpom=pom;
			pom=pom->next;
			if(pom==0)return 0;
		}
		ret=pom->Member;
		if(i==0 && numOfMembers==1)
		{
			first=last=0;

		}
		else if (i==0)
		{
			first=first->next;

		}
		else if(i==numOfMembers-1 && i!=0)
		{
			last=befpom;

		}
		else
		{
			befpom->next=pom->next;

		}
		delete pom;
		numOfMembers--;
		return ret;
	}

	void putIterratorOnFirstPlace(){iterrator=first;}

	T showThenNextIterrator()
	{
		if(iterrator==0)return 0;
		else
		{
		T ret=iterrator->Member;
		iterrator=iterrator->next;
		return ret;
		}
	}
};



#endif /* LIST_H_ */
