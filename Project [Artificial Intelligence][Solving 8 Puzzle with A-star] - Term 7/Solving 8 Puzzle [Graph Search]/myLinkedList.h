struct stateNode
{
    short tiles[9];
    char action; // ACTIONS = {INITIALIZE, UP, DOWN, LEFT, RIGHT}
    short depth;
    short h1; // NUMBER OF MISPLACED TILES
    short h2; // MANHATTEN DISTANCE
    short h3; // HOMEWORK
    stateNode* PARENT;
    stateNode* NEXT;
};

class linkedList
{
    /* GRAPH-SEARCH */
    private:
        stateNode* frontNode; // FIRST STATENODE IN FRONTIER_LIST , SORT
        stateNode* frontNode_Explored; // FIRST STATENODE IN EXPLORED_LIST
        short heuristic_number; // CHOOSE HEURISTIC FUNCTION
        bool isEqual(short t1[],short t2[]);
        stateNode* findInFrontier(short targetTiles[]);
        bool isExistInExplored(short targetTiles[]);
        stateNode* prev(stateNode* p);

    public:
        linkedList(){frontNode=NULL; frontNode_Explored=NULL; heuristic_number=0; /*DEFAULT HEURISTIC FUNCTION*/}

        bool isEmpty(){return frontNode==NULL;}
        void hSelect(short h_number){heuristic_number=h_number;}
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
    int cur_f,new_f;
    for(short i=0;i<9;i++)
        newNode->tiles[i]=tiles[i];
    newNode->action=action;
    newNode->depth=depth;
    newNode->h1=heuristic_1(tiles);
    newNode->h2=heuristic_2(tiles);
    newNode->h3=heuristic_3(tiles);
    newNode->PARENT=parent;

    /**/
    if(isExistInExplored(tiles))
        return;
    /**/

    switch(heuristic_number)
    {
        case 0:
            new_f = depth; break;
        case 1:
            new_f = depth + newNode->h1; break;
        case 2:
            new_f = depth + newNode->h2; break;
        default:
            new_f = depth + newNode->h3;
    }

    /**/
    stateNode* inFrontier=findInFrontier(tiles);
    if(inFrontier!=NULL)
    {
        switch(heuristic_number)
        {
            case 0:
                if(inFrontier->depth < new_f) return;
                break;
            case 1:
                if(inFrontier->depth+inFrontier->h1 < new_f) return;
                break;
            case 2:
                if(inFrontier->depth+inFrontier->h2 < new_f) return;
                break;
            default:
                if(inFrontier->depth+inFrontier->h3 < new_f) return;
        }
        stateNode* p=prev(inFrontier);
        if(p==NULL)
            frontNode=inFrontier->NEXT;
        else
            p->NEXT=inFrontier->NEXT;
        delete inFrontier;
    }
    /**/

    while(current!=NULL)
    {
        switch(heuristic_number)
        {
            case 0:
                cur_f = current->depth; break;
            case 1:
                cur_f = current->depth + current->h1; break;
            case 2:
                cur_f = current->depth + current->h2; break;
            default:
                cur_f = current->depth + current->h3;
        }
        if(new_f<cur_f)
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
