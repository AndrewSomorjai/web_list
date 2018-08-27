#include <emscripten/bind.h>
#include <emscripten/emscripten.h>  

using namespace emscripten;

struct node
{
	int data;
	node *next;	
};
class list
{
		private:
		
			node *head, *tail;
		
		public:
		list()
		{
			head=NULL;
			tail=NULL;
		}		
		void createnode(int value)
		{
			EM_ASM_({
				  console.log('	createnode: ' + $0);
				}, value);
			node *temp=new node;
			temp->data=value;
			temp->next=NULL;
			if(head==NULL)
			{
				head=temp;
				tail=temp;
				temp=NULL;
			}
			else
			{	
				tail->next=temp;
				tail=temp;
			}
		}		
		void display()
		{
			node *temp=new node;
			temp=head;
			while(temp!=NULL)
			{				
				EM_ASM_({
				  console.log('	temp->data: ' + $0);
				}, temp->data);
				
				temp=temp->next;
			}
		}	
			
		int return_first() const 
		{ 
			int x;
			x = head->data; 
			return x;
		}			
		
		void delete_first()
		{
			node *temp=new node;
			temp=head;
			head=head->next;
			delete temp;
		}
		void delete_last()
		{
			node *current=new node;
			node *previous=new node;
			current=head;
			while(current->next!=NULL)
			{
				previous=current;
				current=current->next;	
			}
			tail=previous;
			previous->next=NULL;
			delete current;
		}		
};

EMSCRIPTEN_BINDINGS(linked_list) 
{
  class_<list>("list")
    .constructor()
    .function("createnode", &list::createnode)  
	.function("display", &list::display)  		
	.function("return_first", &list::return_first) 
	.function("delete_first", &list::delete_first)  
	.function("delete_last", &list::delete_last)  
	.property("x", &list::return_first)	
    ;
}
