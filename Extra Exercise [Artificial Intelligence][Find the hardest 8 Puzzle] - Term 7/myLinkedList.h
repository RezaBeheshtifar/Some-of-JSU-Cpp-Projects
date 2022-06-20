struct stateNode
{
    short tiles[9];
    char action; // ACTIONS = {INITIALIZE, UP, DOWN, LEFT, RIGHT}
    short depth;
    stateNode* PARENT;
    stateNode* NEXT;
};

class linkedList
{
    /* GRAPH-SEARCH */
    private:
        stateNode* frontNode; // FIRST STATENODE IN FRONTIER_LIST , SORT
        stateNode* frontNode_Explored; // FIRST STATENODE IN EXPLORED_LIST
        bool isEqual(short t1[],short t2[]);
        stateNode* findInFrontier(short targetTiles[]);
        bool isExistInExplored(short targetTiles[]);
        stateNode* prev(stateNode* p);

    public:
        linkedList(){frontNode=NULL; frontNode_Explored=NULL;}

        bool isEmpty(){return frontNode==NULL;}
        void add_graphSearch(short tiles[],char action,short depth,stateNode* parent);
        stateNode* removeAndReturnAddress(); // SORT
        void printSolution(stateNode* n);

        int size_Frontier(); // NOT NECESSARY
        int size_Explored(); // NOT NECESSARY
        void delete_All(); // NOT NECESSARY
};

bool linkedList::isEqual(short t1[],short t2[])
{
    for(short i=0;i<9;i++)
        if(t1[i]!=t2[i])
            return false;
    return true;
}

stateNode* linkedList::findInFrontier(short targetTiles[])
{
    stateNode* current=frontNode;
    while(current!=NULL)
    {
        if(isEqual(targetTiles,current->tiles))
            return current;
        current=current->NEXT;
    }
    return NULL;
}

bool linkedList::isExistInExplored(short targetTiles[])
{
    stateNode* current=frontNode_Explored;
    while(current!=NULL)
    {
        if(isEqual(targetTiles,current->tiles))
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

void linkedList::add_graphSearch(short tiles[],char action,short depth,stateNode* parent)
{
    stateNode* newNode = new stateNode;
    stateNode* current = frontNode;
    stateNode* last = NULL;
    for(short i=0;i<9;i++)
        newNode->tiles[i]=tiles[i];
    newNode->action=action;
    newNode->depth=depth;
    newNode->PARENT=parent;

    if(isExistInExplored(tiles))
        return;

    stateNode* inFrontier=findInFrontier(tiles);
    if(inFrontier!=NULL)
    {
        if(inFrontier->depth < depth)
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
        if(depth<current->depth)
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

void linkedList::printSolution(stateNode* n)
{
    if(n==NULL)
        return;
    printSolution(n->PARENT);
    saveToFile(n->tiles);
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
