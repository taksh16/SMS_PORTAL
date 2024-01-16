#include<iostream>
#include<vector>
#include<stdio.h>
#include<string>
#include<fstream>
using namespace std;
class node{
    public :
    string to="",from="",date="",message_details="",email_id="";
    node* next;
    node(string f_msg,string t_msg,string d,string message_dat,string emailid){
        from = f_msg;
        to = t_msg;
        date = d;
        message_details = message_dat;
        email_id=emailid;
        next = NULL;
    }
};
void searchr(node*head,string target){
    int cnt=0;
    node*tmp = head;
    bool flag = false;
    while(tmp!=nullptr){
        if(tmp->to == target){
            cnt++;
            flag = true;
        }
        tmp = tmp->next;
    }
    if(cnt>1){
        string email;
        cout<<"There are more than 1 recievers of same name, Please enter email address of reciever : ";
        cin>>email;
        node *t=head;
        while(t!=nullptr){
            if(t->email_id==email){
                flag=true;
                cout<<"Details"<<"\n";
                cout<<"Sender : "<<t->from<<"\n";
                cout<<"Receiver : "<<t->to<<"\n";
                cout<<"Message : "<<t->message_details<<"\n";
                cout<<"Email ID: "<<t->email_id<<"\n";
                cout<<"Date : "<<t->date<<"\n";
                return;
            }
            t=t->next;
        }
    }else if(cnt==1){
        cout<<"Details"<<"\n";
        cout<<"Sender : "<<tmp->from<<"\n";
        cout<<"Receiver : "<<tmp->to<<"\n";
        cout<<"Message : "<<tmp->message_details<<"\n";
        cout<<"Email ID: "<<tmp->email_id<<"\n";
        cout<<"Date : "<<tmp->date<<"\n";
    }
    if(!flag) printf("INVALID SEARCH\n");
    return;
}
void searchkeyword(node*head,string target){
    node*tmp = head;
    int check=0;
    while(tmp!=nullptr){
      int flag =tmp->message_details.find(target);
      if(flag!=string::npos){
            check=1;
            cout<<"Details"<<"\n";
            cout<<"Sender : "<<tmp->from<<"\n";
            cout<<"Receiver : "<<tmp->to<<"\n";
            cout<<"Message : "<<tmp->message_details<<"\n";
            cout<<"Email ID: "<<tmp->email_id<<"\n";
            cout<<"Date : "<<tmp->date<<"\n";
      }
      tmp = tmp->next;
    }
    if(check!=1) printf("No Such message with keyword exists\n");
    return;
}
void searchs(node*head,string target){
    node*tmp = head;
    bool flag = false;
    while(tmp!=nullptr){
        if(tmp->from == target){
            flag = true;
            cout<<"Details"<<"\n";
            cout<<"Sender : "<<tmp->from<<"\n";
            cout<<"Receiver : "<<tmp->to<<"\n";
            cout<<"Message : "<<tmp->message_details<<"\n";
            cout<<"Email ID: "<<tmp->email_id<<"\n";
            cout<<"Date : "<<tmp->date<<"\n";
        }
        tmp = tmp->next;
    }
    if(!flag) printf("INVALID SEARCH\n");
    return;
}
void searchd(node*head,string target){
    node*tmp = head;
    bool flag = false;
    while(tmp != nullptr){
        if(tmp->date == target){
            flag = true;
            cout<<"Details"<<"\n";
            cout<<"Sender : "<<tmp->from<<"\n";
            cout<<"Receiver : "<<tmp->to<<"\n";
            cout<<"Message : "<<tmp->message_details<<"\n";
            cout<<"Email ID: "<<tmp->email_id<<"\n";
            cout<<"Date : "<<tmp->date<<"\n";
        }
        tmp = tmp->next;
    }
    if(!flag) printf("INVALID SEARCH\n");
    return;
}
void display(node*&head){
    node *tmp=head;
    while(tmp!=nullptr){
        cout<<"Sender : "<<tmp->from<<"\n";
        cout<<"Receiver : "<<tmp->to<<"\n";
        cout<<"Message : "<<tmp->message_details<<"\n";
        cout<<"Email ID: "<<tmp->email_id<<"\n";
        cout<<"Date : "<<tmp->date<<"\n";
        tmp = tmp->next;
    }
    return;
}
void send(node*&head,node*&tail){
    string from,to,message_details,date,email_id;
    printf("from : ");
    getline(cin,from);
    printf("to : ");
    getline(cin,to);
    printf("Enter your message : ");
    getline(cin,message_details);
    printf("Enter the email id of reciever: ");
    getline(cin,email_id);
    printf("enter date (dd/mm/yyyy) : ");
    getline(cin,date);
    if(head == nullptr){
        tail = new node(from,to,date,message_details,email_id);
        head = tail;
    }
    else{
        node*dat = new node(from,to,date,message_details,email_id);
        tail->next = dat;
        tail = tail->next;
        tail->next = nullptr;
    }
    return;
}
void deletemsg(node* &head,string target){
   node* curr=head;
   node* prev=NULL;
   ofstream outFile("deleted_sms.txt", ios::app);
   while(curr!= nullptr){
      int ind=curr->message_details.find(target);
      if(ind!= string::npos) {
         if(prev!= nullptr) {
            prev->next=curr->next;
         } else {
            head=curr->next;
         }
         outFile<<"from: "<<curr->from<<endl<<"to: "<<curr->to<<endl<<"Message: "<< curr->message_details<<endl<<"Date: "<< curr->date<<"Email ID: "<<curr->email_id<<endl;
         delete curr;
         cout << "SMS is deleted and stored in 'deleted_sms.txt'." << endl;
         return;
      }
      prev=curr;
      curr=curr->next;
   }
   outFile.close();
   cout << "No matching SMS found for deletion." << endl;
}
int main(){
    node*head = nullptr,*tail = nullptr;
    do{
        printf("Please select one of operations to be performed : \n");
        printf("1.To send SMS\n");
        printf("2.To display SMS\n");
        printf("3.To search SMS\n");
        printf("4.To delete SMS\n");
        printf("Enter your choice : ");
        int option = 0;
        scanf("%d",&option);
        cin.ignore();
        switch(option){
            case 1 : 
                send(head,tail);
                break;
            case 2 : 
                display(head);
                break;
            case 3 : 
                {
                    printf("Which search type of do you want to do ? (options : from,to,date,keyword) ");
                    string s,x;
                    getline(cin,s);
                    printf("Enter target : ");
                    getline(cin,x);
                    if(s == "to") searchr(head,x);
                    else if(s == "from") searchs(head,x);
                    else if(s == "date") searchd(head,x);
                    else if(s == "keyword") searchkeyword(head,x);
                    break;
                }
            case 4 :
                {
                    printf("Enter the keyword in the message which you want to delete: ");
                    string keyw;
                    getline(cin,keyw);
                    deletemsg(head,keyw);
                    break;
                }
        }
        char ch;
        printf("Do you wish to perform another operation ?\n");
        printf("If yes then enter Y else enter N :");
        scanf("%c",&ch);
        if(ch =='N') break;
    }while(1);
}