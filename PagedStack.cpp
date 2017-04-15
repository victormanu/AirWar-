#include<iostream>
#include<string>
#include "PagedStack.h"
using namespace std;



// PUSH Operation
void PagedStack::push(int identificador,int puntaje_Asociado,string tipo,int velocidad,int ataque,
                      int resistencia,int vida,int x,int y)
{

    struct node *ptr;
    cout<<"PUSH Operationn";
    cout<<"Enter a number to insert: ";
    //cin>>value;
    ptr=new node;
    ptr->data=identificador;
    ptr->next=NULL;
    if(top!=NULL)
        ptr->next=top;
    top=ptr;
    //paginacion
    ofstream myfile;
    myfile.open ("Stack"+to_string(identificador)+".txt");
    myfile << to_string(puntaje_Asociado)+"\n";
    myfile << tipo+"\n";
    myfile << to_string(velocidad)+"\n";
    myfile << to_string(ataque)+"\n";
    myfile << to_string(resistencia)+"\n";
    myfile << to_string(vida)+"\n";
    myfile << to_string(x)+"\n";
    myfile << to_string(y)+"\n";
    myfile.close();




    cout<<"New item is inserted to the stack!!!";

}

// POP Operation
void PagedStack::pop()
{
    struct node *temp;
    if(top==NULL)
    {
        cout<<"nThe stack is empty!!!";
    }
    temp=top;
    top=top->next;
    cout<<"POP Operation........Poped value is "<<temp->data<<endl;
    //cout<<temp->data<<endl;
    /*ifstream myfile("Stack"+to_string(temp->data)+".txt");
    string Extraction;

    if(!myfile)
    {
        cout<<"Error opening output file"<<endl;
        system("pause");
        //return -1;
    }

        cout<<"identificador: "<<temp->data<<"\n";
        //identificador=temp->data;
        getline(myfile,Extraction,'\n');
        //puntaje_Asociado=Extraction;
        cout<<"puntaje_Asociado: "<<Extraction<<"\n";
        getline(myfile,Extraction,'\n');
        //tipo=Extraction;
        cout<<"tipo: "<<Extraction<<"\n";
        getline(myfile,Extraction,'\n');
        //velocidad=Extraction;
        cout<<"velocidad: "<<Extraction<<"\n";
        getline(myfile,Extraction,'\n');
        //ataque=Extraction;
        cout<<"ataque: "<<Extraction<<"\n";
        getline(myfile,Extraction,'\n');
        //resistencia=Extraction;
        cout<<"resistencia: "<<Extraction<<"\n";
        getline(myfile,Extraction,'\n');
        //vida=Extraction;
        cout<<"vida: "<<Extraction<<"\n";
        getline(myfile,Extraction,'\n');
        //x=Extraction;
        cout<<"x: "<<Extraction<<"\n";
        getline(myfile,Extraction,'\n');
        //y=Extraction;
        cout<<"y: "<<Extraction<<"\n";
        getline(myfile,Extraction,'\n');
*/

    delete temp;
}




// Show stack
void PagedStack::show()
{
    struct node *ptr1=top;
    cout<<"nThe stack isn";
    while(ptr1!=NULL)
    {
        cout<<ptr1->data<<" ->";
        ptr1=ptr1->next;
    }
    cout<<"NULL";
}
bool PagedStack::Elements()
{    struct node *ptr1=top;
	if(ptr1!=NULL)
		return true;
	else{return false;}
}
int PagedStack::elementcount()
{      struct node *ptr1=top;

int counter=0;
while(ptr1!=NULL)
{
    counter++;
    ptr1=ptr1->next;
}
return counter;
}

