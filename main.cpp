#include<bits/stdc++.h>

using namespace std;



struct Node
{
    char track[100];
    struct Node *next;
    struct Node *prev;
}*top,*temp,*top1;

void writeToFile(char track[])
{
    fstream file;
    file.open("playlist.txt",ios::out|ios::app);
    file<<track<<endl;
    file.close();
}

void addNode(struct Node *first)
{
    char track[100];
    while(first->next!=NULL)
    {
        first=first->next;
    }
    first->next=(struct Node*)malloc(sizeof(struct Node));
    first->prev=first;
    first=first->next;
    cout<<"\nEnter track name: ";
    scanf("%s",&track);
    strcpy(first->track,track);
    writeToFile(track);
    first->next=NULL;
}

void addNodeFromFile(struct Node *first,string track)
{
    while(first->next!=NULL)
    {
        first=first->next;
    }
    first->next=(struct Node*)malloc(sizeof(struct Node));
    first->prev=first;
    first=first->next;
    strcpy(first->track,track.c_str());
    first->next=NULL;
}

void deleteFromFile(char track[])
{
    fstream file1,file2;
    string line;
    int x=0;
    file1.open("playlist.txt",ios::in|ios::out);
    file2.open("temp.txt",ios::in|ios::out);
    while(!file1.eof())
    {
        getline(file1,line);
        if(strcmp(track,line.c_str())!=0)
        file2<<line<<endl;
        else if (strcmp(track,line.c_str())==0)
        x=1;
    }
    file1.close();
    file2.close();
    remove("playlist.txt");
    rename("temp.txt","playlist.txt");
    if(x==0)
        {
        cout << "There is no track with the name you entered." << endl;
        }
    else
        {
        cout << "Track has been deleted." << endl;
        }
}

void deleteNode(struct Node *first)
{
    while((first->next)->next!=NULL)
    {
        first=first->next;
    }
    struct Node *temp;
    temp=(first->next)->next;
    first->next=NULL;
    free(temp);
    cout<<"Deleted"<<endl;
}

void printList(struct Node *first)
{
    cout<<"\nPlaylist Name: ";
    while(first->next!=NULL)
    {
        cout<<first->track<<endl;
        first=first->next;
    }
    cout<<first->track<<endl;
}

void countNodes(struct Node *first)
{
    int i=0;
    while (first->next!=NULL)
    {
        first=first->next;
        i++;
    }
    i++;
    cout<<"\nTotal tracks: "<<i-1<<endl;
}

struct Node  *deletePosition(struct Node *pointer, int pos)
{
    struct Node *n1,*prev1,*temp;
    prev1= ( struct Node *)malloc(sizeof(Node));
    temp= (struct Node *)malloc(sizeof(Node));
    int i=0;

    if(pos==1)
    {
        temp=pointer;
        deleteFromFile(temp->track);
        pointer=pointer->next;
        pointer->prev = NULL;
        free(temp);
        printf("\nThe list is updated.\nUse the display function to check.\n");
        return pointer;
    }
    while(i<pos-1)
    {
        prev1=pointer;
        pointer=pointer->next;
        i++;
    }

    if(pointer->next==NULL)
    {
        temp=pointer;
        deleteFromFile(temp->track);
        prev1->next->prev=NULL;
        prev1->next=NULL;
        free(temp);
        printf("\nThe list is updated.\nUse the display function to check.\n");
    }
    else
    {
        temp=pointer;
        deleteFromFile(temp->track);
        prev1->next=temp->next;
        temp->next->prev=prev1;
        free(temp);
        printf("\nThe list is updated.\nUse the display function to check.\n");
    }
}

void searchTrack(struct Node *first)
{
    char track[100];
    cout<<"\nEnter track to be searched: ";
    scanf("%s",&track);
    int flag=0;

    while(first!=NULL)
    {
        if(strcmp(first->track,track)==0)
        {
            cout<<"\nTrack Found."<<endl;
            flag++;
            break;
        }
        else
        {
            first=first->next;
        }
    }
    if(flag==0)
    {
        cout<<"\nTrack Not found."<<endl;
    }
}

void initialize()
{
    top = NULL;
}

void pushTrack(char data[])
{
    if (top == NULL)
    {
        top =(struct Node *)malloc(sizeof(struct Node));
        top->next = NULL;
        strcpy(top->track,data);
    }
    else if (strcmp(top->track,data)!=0)
    {
        temp =(struct Node *)malloc(sizeof(struct Node));
        temp->next = top;
        strcpy(temp->track,data);
        top = temp;
    }
}

void displayRecentTracks()
{
    top1 = top;
    if (top1 == NULL)
    {
        printf("\n=>NO recently played tracks.\n");
        return;
    }
    printf("\n#Recently played tracks:\n");
    while (top1 != NULL)
    {
        printf("%s", top1->track);
        printf("\n");
        top1 = top1->next;
    }
 }

void playTrack(struct Node *first)
{
    char track[100];
    printList(first);
    cout<<"\nChoose track you wish to play: ";
    scanf("%s",track);
    int flag=0;

    while(first!=NULL)
    {
        if(strcmp(first->track,track)==0)
        {
            cout<<"\nNow Playing: "<<track<<endl;
            flag++;
            pushTrack(track);
            break;
        }
        else
        {
            first=first->next;
        }
    }
    if(flag==0)
    {
        cout<<"\nTrack Not found."<<endl;
    }
}

void displayRecent()
{
    displayRecentTracks();
}

void lastPlayedTrack()
{
    top1=top;
    if(top1==NULL)
    {
        printf("\n#NO last played tracks.\n");
        return;
    }
    cout<<"\nLast Played Track: "<<top->track<<endl;
}

void sortTracks(struct Node *&pointer)
{
    struct Node *a = NULL;
    struct Node *b = NULL;
    struct Node *c = NULL;
    struct Node *e = NULL;
    struct Node *tmp = NULL;
    while(e != pointer->next)
    {
        c = a = pointer;
        b = a->next;
        while(a != e)
        {
            if(strcmp(a->track,a->track))
            {
                if(a == pointer)
                {
                    tmp = b -> next;
                    b->next = a;
                    a->next = tmp;
                    pointer = b;
                    c = b;
                }
                else
                {
                    tmp = b->next;
                    b->next = a;
                    a->next = tmp;
                    c->next = b;
                    c = b;
                }
            }
            else
            {
                c = a;
                a = a->next;
            }
            b = a->next;
            if(b == e)
                e = a;
        }
    }
}

void addPlaylist(struct Node *start)
{
    fstream file;
    string line;
    file.open("playlist.txt",ios::in);
    while(!file.eof())
    {
        getline(file,line);
        addNodeFromFile(start,line);
    }
    cout<<"Playlist Added"<<endl;
    file.close();
}

void deleteSearch(struct Node *start)
{
    char track[100];
    printList(start);
    cout<<"\nChoose track you wish to delete: ";
    scanf("%s",track);
    int flag=0;
    while(start!=NULL)
    {
        if(strcmp(start->track,track)==0)
        {
            cout<<"\nTrack Found."<<endl;
            struct Node *temp;
            temp= (struct Node *)malloc(sizeof(Node));
            temp=start;
            deleteFromFile(temp->track);
            temp->prev->next=temp->next;
            temp->next->prev=temp->prev;
            free(temp);
            flag++;
            break;
        }
        else
        {
            start=start->next;
        }
    }
    if(flag==0)
    {
        cout<<"\nTrack Not found."<<endl;
    }
}

void deleteMenu(struct Node *start)
{
    int c;
    cout<<"Which type of delete do you want?\n1.By Search\n2.By Position"<<endl;
    cin>>c;
    switch(c)
    {
    case 1:deleteSearch(start);
    break;
    case 2:int pos;
            printf("\nEnter the pos of the track : ");
            scanf("%d",&pos);
            deletePosition(start,pos-1);
    break;
    }
}

int main()
{
    int choice;
    struct Node *start,*hold;
    start=(struct Node *) malloc(sizeof(struct Node));
    cout<<"\t\t\t*WELCOME*"<<endl;
    cout<<"\n**please use '_' for space."<<endl;
    cout<<"\n\nEnter your playlist name:  ";
    cin.getline(start->track,100);
    start->next=NULL;
    hold=start;
    initialize();

    do{
        cout<<"\n1.Add New Track\n2.Delete Track\n3.Display Entered Playlist\n4.Total Tracks\n5.Search Track\n6.Play Track\n7.Recently Played List\n8.Last Played\n9.Sorted playlist\n10.Add From File\n11.Exit"<<endl;
        cout<<("\nEnter your choice: ");
        cin>>choice;

        switch(choice)
        {
            case 1:addNode(start);
            break;
            case 2:deleteMenu(start);
            break;
            case 3:printList(start);
            break;
            case 4:countNodes(hold);
            break;
            case 5:searchTrack(start);
            break;
            case 6:playTrack(start);
            break;
            case 7:displayRecent();
            break;
            case 8:lastPlayedTrack();
            break;
            case 9:sortTracks(start->next);
            printList(start);
            break;
            case 10:addPlaylist(start);
            break;
            case 11:exit(0);
        }
    }while(choice!=11);
    return 0;
}
