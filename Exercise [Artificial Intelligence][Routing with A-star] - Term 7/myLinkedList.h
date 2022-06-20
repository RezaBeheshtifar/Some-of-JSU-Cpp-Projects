struct stateNode
{
    position pos;
    char action; // ACTIONS={START,UP,DOWN,LEFT,RIGHT}
    short g;
    short f;
    stateNode* PARENT;
    stateNode* NEXT;
};

class linkedList
{
    /* GRAPH-SEARCH */
    private:
        stateNode* frontNode; // FIRST STATENODE IN FRONTIER_LIST , SORT
        stateNode* frontNode_Explored; // FIRST STATENODE IN EXPLORED_LIST
        bool isEqual(const position p1,const position p2);
        stateNode* findInFrontier(const position p);
        bool isExistInExplored(const position p);
        stateNode* prev(stateNode* p);

    public:
        linkedList(){frontNode=NULL; frontNode_Explored=NULL;}

        bool isEmpty(){return frontNode==NULL;}
        void add_graphSearch(position p,char action,char g,short h,stateNode* parent);
        stateNode* removeAndReturnAddress(); // SORT
        void printSolution1(stateNode* n);
        void printSolution2(stateNode* n);

        int size_Frontier(); // NOT NECESSARY
        int size_Explored(); // NOT NECESSARY
        void delete_All(); // NOT NECESSARY
};

bool linkedList::isEqual(const position p1,const position p2)
{
    return ((p1.i==p2.i) && (p1.j==p2.j));
}

stateNode* linkedList::findInFrontier(const position p)
{
    stateNode* current=frontNode;
    while(current!=NULL)
    {
        if(isEqual(p,current->pos))
            return current;
        current=current->NEXT;
    }
    return NULL;
}

bool linkedList::isExistInExplored(const position p)
{
    stateNode* current=frontNode_Explored;
    while(current!=NULL)
    {
        if(isEqual(p,current->pos))
            return true;
        current=current->NEXT;
    }
    return false;
}

stateNode* linkedList::prev(stateNode* p){
    if(p==frontNode || p==NULL)
        return NULL;
    stateNode* current=frontNode;
    while(current->NEXT!=p)
        current=current->NEXT;
    return current;
}

void linkedList::add_graphSearch(position p,char action,char g,short h,stateNode* parent)
{
    stateNode* newNode = new stateNode;
    stateNode* current = frontNode;
    stateNode* last = NULL;
    newNode->pos=p;
    newNode->action=action;
    if(parent!=NULL)
        newNode->g=g+parent->g;
    else
        newNode->g=g;
    if(parent!=NULL)
        newNode->f=g+parent->g+h;
    else
        newNode->f=g+h;
    newNode->PARENT=parent;

    if(isExistInExplored(p))
        return;

    stateNode* inFrontier=findInFrontier(p);
    if(inFrontier!=NULL)
    {
        if(inFrontier->f < newNode->f)
            return;
        stateNode* p=prev(inFrontier);
        if(p==NULL)
            frontNode=inFrontier->NEXT;
        else
            p->NEXT=inFrontier->NEXT;
        delete inFrontier;
    }

    while(current!=NULL)
    {
        if(newNode->f < current->f)
        {
            // INSERT BEFORE CURRENT
            if(last==NULL)
            {
                newNode->NEXT=frontNode; frontNode=newNode;
            }
            else
            {
                last->NEXT=newNode; newNode->NEXT=current;
            }
            return;
        }
        last=current;
        current=current->NEXT;
    }

    if(last==NULL)
    {
        newNode->NEXT=frontNode; frontNode=newNode;
    }
    else
    {
        last->NEXT=newNode; newNode->NEXT=NULL;
    }
}

stateNode* linkedList::removeAndReturnAddress()
{
    stateNode* min_node=frontNode;
    if(min_node==NULL)
        return NULL;
    // REMOVE FROM FRONTIER_LIST
    frontNode=frontNode->NEXT;
    // ADD TO EXPLORED_LIST
    min_node->NEXT=frontNode_Explored;
    frontNode_Explored=min_node;
    return min_node;
}

void linkedList::printSolution1(stateNode* n)
{
    if(n==NULL)
        return;
    printSolution1(n->PARENT);
    showOnScreen(n->pos,n->action);
}

void linkedList::printSolution2(stateNode* n)
{
    if(n==NULL)
        return;
    printSolution2(n->PARENT);
    saveToFile(n->pos,n->action);
}

int linkedList::size_Frontier() // NOT NECESSARY
{
    int n=0;
    stateNode* current=frontNode;
    while(current!=NULL)
    {
        n++;
        current=current->NEXT;
    }
    return n;
}

int linkedList::size_Explored() // NOT NECESSARY
{
    int n=0;
    stateNode* current=frontNode_Explored;
    while(current!=NULL)
    {
        n++;
        current=current->NEXT;
    }
    return n;
}

void linkedList::delete_All() // NOT NECESSARY
{
    // FRONTIER_LIST
    stateNode* current=frontNode;
    while(current!=NULL)
    {
        frontNode=current->NEXT;
        delete current;
        current=frontNode;
    }
    // EXPLORED_LIST
    current=frontNode_Explored;
    while(current!=NULL)
    {
        frontNode_Explored=current->NEXT;
        delete current;
        current=frontNode_Explored;
    }
}
