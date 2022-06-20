#define menuColor "color 1F"
#define relationColor "color 3F"

struct myTime
{
    string date;
};

struct Individual_Mar                //Individual_Marriage Node; Dual Task
{
    string name;
    unsigned SSN;
    char sex_type;                  //M: male  F: female  V: marriage
    myTime birth_dateMar;
    myTime death_dateMarEnd;
    Individual_Mar* dad_hus;
    Individual_Mar* mom_wife;
    Individual_Mar* latestMar_;
    Individual_Mar* latestChild_;
    Individual_Mar* prevChildOfDad_;
    Individual_Mar* prevChildOfMom_;
    Individual_Mar* _prevMarHus;
    Individual_Mar* _prevMarWife;
    Individual_Mar* right;          //For Binary Search (BST)
    Individual_Mar* left;           //For Binary Search (BST)
};

class familyTree
{
    private:
        Individual_Mar* root;

        Individual_Mar setIndividual_Mar(string name,unsigned ssn,char sex,myTime birth_dateMar,myTime death_dateMarEnd,Individual_Mar* dad_hus,Individual_Mar* mom_wife,Individual_Mar* latestMar_,Individual_Mar* latestChild_,Individual_Mar* prevChildOfDad_,Individual_Mar* prevChildOfMom_,Individual_Mar* _prevMarHus,Individual_Mar* _prevMarWife,Individual_Mar* right,Individual_Mar* left);
        Individual_Mar* setIndividual_MarStar(string name,unsigned ssn,char sex,myTime birth_dateMar,myTime death_dateMarEnd,Individual_Mar* dad_hus,Individual_Mar* mom_wife,Individual_Mar* latestMar_,Individual_Mar* latestChild_,Individual_Mar* prevChildOfDad_,Individual_Mar* prevChildOfMom_,Individual_Mar* _prevMarHus,Individual_Mar* _prevMarWife,Individual_Mar* right,Individual_Mar* left);
        Individual_Mar* convertToIndividual_MarStar(Individual_Mar node);
        Individual_Mar convertToIndividual_Mar(Individual_Mar* node);

        void insert_IndividualNodeToTree_NR(Individual_Mar newNode);
        void inOrder(Individual_Mar* r);

        Individual_Mar* findSSN_R(Individual_Mar* r,unsigned SSN);
        Individual_Mar* findName_R(Individual_Mar* r,string strKey);

        int countNodes(Individual_Mar* r);
        int countLeaf(Individual_Mar* r);
        int maxHeight(Individual_Mar* r);

        void inOrder_Relation_Child(Individual_Mar* r,string name);
        void inOrder_Relation_ChildExceptBoy(Individual_Mar* r,string par,string mom,string exceptBoy);
        void inOrder_Relation_ChildExceptGirl(Individual_Mar* r,string par,string mom,string exceptGirl);
        void inOrder_Relation_ChildExceptGirl_ForBajenagh(Individual_Mar* r,string par,string mom,string exceptGirl);
        void inOrder_Relation_Descendent(string name,Individual_Mar* r);
        Individual_Mar* findFather(Individual_Mar* r);
        Individual_Mar* findGrandFather(Individual_Mar* r);
        Individual_Mar* findGrandFather2nd(Individual_Mar* r);
        Individual_Mar* findMother(Individual_Mar* r);
        Individual_Mar* findGrandMother(Individual_Mar* r);
        Individual_Mar* findGrandMother2nd(Individual_Mar* r);
        void Relation_sister_ForBajenagh(string name,string par,string mom);

        bool isAncestorXY(Individual_Mar* x,Individual_Mar* y);
        bool isDescendentXY(Individual_Mar* x,Individual_Mar* y);

    public:
        familyTree(){root=NULL;}
        bool isEmpty(){if(root==NULL) return true; return false;}

        bool birth(string name,string dad,string mom,char sex,myTime birthDate,unsigned SSN);
        bool death(string name,myTime deathTime);
        bool marriage(string husName,string wifeName,myTime dateMar);
        bool divorce(string husName,string wifeName,myTime dateDiv);

        bool isExistSSN(unsigned SSN);
        Individual_Mar infoSSN(unsigned SSN);
        bool isExistName(string name);
        Individual_Mar infoName(string name);

        void printOne(Individual_Mar p);
        void printAll();

        int countNodes();
        int countLeaf();
        int maxHeight();

        void Relation_Child(string name);
        void Relation_Husband(string name);
        void Relation_Wife(string name);
        void Relation_brother(string name,string par,string mom);
        void Relation_sister(string name,string par,string mom);
        void Relation_GrandFather(string name);
        void Relation_GrandMother(string name);
        void Relation_Ancestor(string name);
        void Relation_Uncel(string name);
        void Relation_Uncel_momBrother(string name);
        void Relation_Aunt(string name);
        void Relation_Aunt_momSister(string name);
        void Relation_FatherOfWife(string name);
        void Relation_MotherOfWife(string name);
        void Relation_FatherOfHus(string name);
        void Relation_MotherOfHus(string name);
        void Relation_Bajenagh(string name);
        void Relation_Descendent(string name);

        void Relation_betweenPeople(string a,string b);
};

Individual_Mar familyTree::setIndividual_Mar(string name,unsigned ssn,char sex,myTime birth_dateMar,myTime death_dateMarEnd,Individual_Mar* dad_hus,Individual_Mar* mom_wife,Individual_Mar* latestMar_,Individual_Mar* latestChild_,Individual_Mar* prevChildOfDad_,Individual_Mar* prevChildOfMom_,Individual_Mar* _prevMarHus,Individual_Mar* _prevMarWife,Individual_Mar* right,Individual_Mar* left)
{
    Individual_Mar r;
	r.name=name;
    r.SSN=ssn;
    r.sex_type=sex;
    r.birth_dateMar=birth_dateMar;
    r.death_dateMarEnd=death_dateMarEnd;
    r.dad_hus=dad_hus;
    r.mom_wife=mom_wife;
    r.latestMar_=latestMar_;
    r.latestChild_=latestChild_;
    r.prevChildOfDad_=prevChildOfDad_;
    r.prevChildOfMom_=prevChildOfMom_;
    r._prevMarHus=_prevMarHus;
    r._prevMarWife=_prevMarWife;
    r.right=right;
    r.left=left;
    return r;
}

Individual_Mar* familyTree::setIndividual_MarStar(string name,unsigned ssn,char sex,myTime birth_dateMar,myTime death_dateMarEnd,Individual_Mar* dad_hus,Individual_Mar* mom_wife,Individual_Mar* latestMar_,Individual_Mar* latestChild_,Individual_Mar* prevChildOfDad_,Individual_Mar* prevChildOfMom_,Individual_Mar* _prevMarHus,Individual_Mar* _prevMarWife,Individual_Mar* right,Individual_Mar* left)
{
    Individual_Mar* r=new Individual_Mar;
	r->name=name;
    r->SSN=ssn;
    r->sex_type=sex;
    r->birth_dateMar=birth_dateMar;
    r->death_dateMarEnd=death_dateMarEnd;
    r->dad_hus=dad_hus;
    r->mom_wife=mom_wife;
    r->latestMar_=latestMar_;
    r->latestChild_=latestChild_;
    r->prevChildOfDad_=prevChildOfDad_;
    r->prevChildOfMom_=prevChildOfMom_;
    r->_prevMarHus=_prevMarHus;
    r->_prevMarWife=_prevMarWife;
    r->right=right;
    r->left=left;
    return r;
}

Individual_Mar* familyTree::convertToIndividual_MarStar(Individual_Mar node)
{
    Individual_Mar* r=new Individual_Mar;
	r->name=node.name;
    r->SSN=node.SSN;
    r->sex_type=node.sex_type;
    r->birth_dateMar=node.birth_dateMar;
    r->death_dateMarEnd=node.death_dateMarEnd;
    r->dad_hus=node.dad_hus;
    r->mom_wife=node.mom_wife;
    r->latestMar_=node.latestMar_;
    r->latestChild_=node.latestChild_;
    r->prevChildOfDad_=node.prevChildOfDad_;
    r->prevChildOfMom_=node.prevChildOfMom_;
    r->_prevMarHus=node._prevMarHus;
    r->_prevMarWife=node._prevMarWife;
    r->right=node.right;
    r->left=node.left;
    return r;
}

Individual_Mar familyTree::convertToIndividual_Mar(Individual_Mar* node)
{
    Individual_Mar r;
	r.name=node->name;
    r.SSN=node->SSN;
    r.sex_type=node->sex_type;
    r.birth_dateMar=node->birth_dateMar;
    r.death_dateMarEnd=node->death_dateMarEnd;
    r.dad_hus=node->dad_hus;
    r.mom_wife=node->mom_wife;
    r.latestMar_=node->latestMar_;
    r.latestChild_=node->latestChild_;
    r.prevChildOfDad_=node->prevChildOfDad_;
    r.prevChildOfMom_=node->prevChildOfMom_;
    r._prevMarHus=node->_prevMarHus;
    r._prevMarWife=node->_prevMarWife;
    r.right=node->right;
    r.left=node->left;
    return r;
}

void familyTree::insert_IndividualNodeToTree_NR(Individual_Mar newNode)
{
    Individual_Mar* temp;
    temp=convertToIndividual_MarStar(newNode);

    Individual_Mar* prep=NULL;
    Individual_Mar* p=root;

    while(p!=NULL)
    {
        prep=p;
        if(newNode.SSN < p->SSN)
            p=p->left;
        else if(newNode.SSN > p->SSN)
            p=p->right;
        else return;
    }
    if(prep==NULL)
        root=temp;
    else if(newNode.SSN < prep->SSN)
        prep->left=temp;
    else if(newNode.SSN > prep->SSN)
        prep->right=temp;
}

void familyTree::inOrder(Individual_Mar* r)
{
    if(r==NULL)
        return;
    else
    {
        inOrder(r->left);
        printOne(convertToIndividual_Mar(r));
        inOrder(r->right);
    }
}

Individual_Mar* familyTree::findSSN_R(Individual_Mar* r,unsigned SSN)
{
    if(r==NULL || r->SSN==SSN)
        return r;
    else if(SSN < r->SSN)
        return findSSN_R(r->left,SSN);
    else
        return findSSN_R(r->right,SSN);
}

Individual_Mar* familyTree::findName_R(Individual_Mar* r,string strKey)
{
    if(r==NULL)
        return NULL;
    else if(r->name==strKey)
        return r;
    else
    {
        Individual_Mar* t1=findName_R(r->left,strKey);
        if(t1!=NULL)
            return t1;
        Individual_Mar* t2=findName_R(r->right,strKey);
        return t2;
    }
}

int familyTree::countNodes(Individual_Mar* r)
{
    if(r==NULL)
        return 0;
    return 1+countNodes(r->left)+countNodes(r->right);
}

int familyTree::countLeaf(Individual_Mar* r)
{
    if(r==NULL)
        return 0;
    else if(r->left==NULL && r->right==NULL)
        return 1;
    return countLeaf(r->left)+countLeaf(r->right);
}

int familyTree::maxHeight(Individual_Mar* r)
{
    if(r==NULL)
        return -1;
    int h=0;
    int h1=maxHeight(r->left);
    int h2=maxHeight(r->right);
    if(h1>h2)
        return h1+1;
    else
        return h2+1;
}

void familyTree::inOrder_Relation_Child(Individual_Mar* r,string name)
{
    if(r==NULL)
        return;
    else
    {
        inOrder_Relation_Child(r->left,name);
        if(r->dad_hus!=NULL && r->dad_hus->name==name)
            printOne(convertToIndividual_Mar(r));
        inOrder_Relation_Child(r->right,name);
    }
}

void familyTree::inOrder_Relation_ChildExceptBoy(Individual_Mar* r,string par,string mom,string exceptBoy)
{
    if(r==NULL)
        return;
    else
    {
        inOrder_Relation_ChildExceptBoy(r->left,par,mom,exceptBoy);
        if(r->dad_hus!=NULL && r->dad_hus->name==par && r->mom_wife!=NULL && r->mom_wife->name==mom && r->name!=exceptBoy && r->sex_type!='F')
            printOne(convertToIndividual_Mar(r));
        inOrder_Relation_ChildExceptBoy(r->right,par,mom,exceptBoy);
    }
}

void familyTree::inOrder_Relation_ChildExceptGirl(Individual_Mar* r,string par,string mom,string exceptGirl)
{
    if(r==NULL)
        return;
    else
    {
        inOrder_Relation_ChildExceptGirl(r->left,par,mom,exceptGirl);
        if(r->dad_hus!=NULL && r->dad_hus->name==par && r->mom_wife!=NULL && r->mom_wife->name==mom && r->name!=exceptGirl && r->sex_type!='M')
            printOne(convertToIndividual_Mar(r));
        inOrder_Relation_ChildExceptGirl(r->right,par,mom,exceptGirl);
    }
}

void familyTree::inOrder_Relation_ChildExceptGirl_ForBajenagh(Individual_Mar* r,string par,string mom,string exceptGirl)
{
    if(r==NULL)
        return;
    else
    {
        inOrder_Relation_ChildExceptGirl_ForBajenagh(r->left,par,mom,exceptGirl);
        if(r->dad_hus!=NULL && r->dad_hus->name==par && r->mom_wife!=NULL && r->mom_wife->name==mom && r->name!=exceptGirl && r->sex_type!='M')
        {
            Individual_Mar* h=r->latestMar_->dad_hus;
            if(h!=NULL)
                printOne(convertToIndividual_Mar(h));
        }
        inOrder_Relation_ChildExceptGirl_ForBajenagh(r->right,par,mom,exceptGirl);
    }
}

void familyTree::inOrder_Relation_Descendent(string name,Individual_Mar* r)
{
    if(r==NULL)
        return;
    else
    {
        inOrder_Relation_Descendent(name,r->left);
        Individual_Mar* g1=findGrandFather(r);
        Individual_Mar* g2=findGrandFather2nd(r);
        if(g1!=NULL && g1->name==name)
            printOne(convertToIndividual_Mar(r));
        else if(g2!=NULL && g2->name==name)
            printOne(convertToIndividual_Mar(r));
        inOrder_Relation_Descendent(name,r->right);
    }
}

Individual_Mar* familyTree::findFather(Individual_Mar* r)
{
    if(r==NULL)
        return NULL;
    return r->dad_hus;
}

Individual_Mar* familyTree::findGrandFather(Individual_Mar* r)
{
    if(r==NULL)
        return NULL;
    return findFather(r->dad_hus);
}

Individual_Mar* familyTree::findGrandFather2nd(Individual_Mar* r)
{
    if(r==NULL)
        return NULL;
    return findFather(r->mom_wife);
}

Individual_Mar* familyTree::findMother(Individual_Mar* r)
{
    if(r==NULL)
        return NULL;
    return r->mom_wife;
}

Individual_Mar* familyTree::findGrandMother(Individual_Mar* r)
{
    if(r==NULL)
        return NULL;
    return findMother(r->mom_wife);
}

Individual_Mar* familyTree::findGrandMother2nd(Individual_Mar* r)
{
    if(r==NULL)
        return NULL;
    return findMother(r->dad_hus);
}

void familyTree::Relation_sister_ForBajenagh(string name,string par,string mom)
{
    if(isExistName(par)==false || isExistName(mom)==false)
        return;
    system(relationColor);
    Individual_Mar* r1=findName_R(root,par);
    Individual_Mar* r2=findName_R(root,mom);
    if(r1==NULL && r2==NULL)
    {
        cout << "\n >>> Information:\n\n Not Found.\n\n " << endl;
        system(menuColor);
        return;
    }
    else if(r1==NULL)
    {
        inOrder_Relation_ChildExceptGirl_ForBajenagh(root,"",mom,name);
        system(menuColor);
        return;
    }
    else if(r2==NULL)
    {
        inOrder_Relation_ChildExceptGirl_ForBajenagh(root,par,"",name);
        return;
    }
    inOrder_Relation_ChildExceptGirl_ForBajenagh(root,par,mom,name);
    system(menuColor);
}

bool familyTree::isAncestorXY(Individual_Mar* x,Individual_Mar* y)
{
    if(x==NULL || y==NULL)
        return false;
    Individual_Mar* r=y;
    while(r!=NULL && r!=x)
        r=r->dad_hus;
    if(r==NULL)
        return false;
    else
        return true;
}

bool familyTree::isDescendentXY(Individual_Mar* x,Individual_Mar* y)
{
    return isAncestorXY(y,x);
}

bool familyTree::birth(string name,string dad,string mom,char sex,myTime birthDate,unsigned SSN)
{
    if(isExistSSN(SSN)==true)
        return false;
    if(sex!='M' && sex!='F')
        return false;
    Individual_Mar newNode;
    newNode=setIndividual_Mar(name,SSN,sex,birthDate,{""},findName_R(root,dad),findName_R(root,mom),NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
    insert_IndividualNodeToTree_NR(newNode);
    Individual_Mar* ok=findName_R(root,name);
    Individual_Mar* father=findName_R(root,dad);
    Individual_Mar* mother=findName_R(root,mom);
    if(father!=NULL)
        father->latestChild_=ok;
    if(mother!=NULL)
        mother->latestChild_=ok;
    return true;
}

bool familyTree::death(string name,myTime deathTime)
{
    if(isExistName(name)==false)
        return false;
    Individual_Mar* t=findName_R(root,name);
    if(t->death_dateMarEnd.date=="")
    {
        t->death_dateMarEnd=deathTime;
        return true;
    }
    return false;
}

bool familyTree::marriage(string husName,string wifeName,myTime dateMar)
{
    if(isExistName(husName)==false || isExistName(wifeName)==false)
        return false;
    Individual_Mar* hus=findName_R(root,husName);
    Individual_Mar* wife=findName_R(root,wifeName);
    Individual_Mar* newNode;
    newNode=setIndividual_MarStar("",0,'V',dateMar,{""},hus,wife,NULL,NULL,NULL,NULL,hus->latestMar_,wife->latestMar_,NULL,NULL);
    hus->latestMar_=newNode;
    wife->latestMar_=newNode;
    return true;
}

bool familyTree::divorce(string husName,string wifeName,myTime dateDiv)
{
    Individual_Mar* pointerHus=findName_R(root,husName);
    Individual_Mar* pointerWife=findName_R(root,wifeName);
    if(pointerHus==NULL || pointerWife==NULL || pointerHus->latestMar_==NULL || pointerWife->latestMar_==NULL || pointerHus->latestMar_->mom_wife->name!=wifeName || pointerWife->latestMar_->dad_hus->name!=husName)
        return false;
    else
    {
        pointerHus->latestMar_->death_dateMarEnd=dateDiv;
        pointerWife->latestMar_->death_dateMarEnd=dateDiv;
        return true;
    }
}

bool familyTree::isExistSSN(unsigned SSN)
{
    Individual_Mar* temp=findSSN_R(root,SSN);
    if(temp!=NULL)
        return true;
    return false;
}

Individual_Mar familyTree::infoSSN(unsigned SSN)
{
    return convertToIndividual_Mar(findSSN_R(root,SSN));
}

bool familyTree::isExistName(string name)
{
    Individual_Mar* temp=findName_R(root,name);
    if(temp!=NULL)
        return true;
    return false;
}

Individual_Mar familyTree::infoName(string name)
{
    return convertToIndividual_Mar(findName_R(root,name));
}

void familyTree::printOne(Individual_Mar p)
{
    system("cls");
    cout << "\n >>> Information:" << endl;
    string sex_type,dad_hus="",mom_wife="",latestMar_="",latestChild_="",prevChildOfDad_="",prevChildOfMom_="",isDivorced="";
    if(p.sex_type=='M')
        sex_type="male";
    else if(p.sex_type=='F')
        sex_type="female";
    if(p.dad_hus!=NULL)
        dad_hus=p.dad_hus->name;
    if(p.mom_wife!=NULL)
        mom_wife=p.mom_wife->name;
    if(p.latestMar_!=NULL)
    {
        if(p.sex_type=='M')
            latestMar_=p.latestMar_->mom_wife->name;
        else
            latestMar_=p.latestMar_->dad_hus->name;

        if(p.latestMar_->death_dateMarEnd.date!="")
            isDivorced=" (Divorced)";
    }
    if(p.latestChild_!=NULL)
        latestChild_=p.latestChild_->name;
    if(p.prevChildOfDad_!=NULL)
        prevChildOfDad_=p.prevChildOfDad_->name;
    if(p.prevChildOfMom_!=NULL)
        prevChildOfMom_=p.prevChildOfMom_->name;
    cout << "\n\n Name:                     " << p.name
         << "\n SSN:                      " << p.SSN
         << "\n Sex:                      " << sex_type
         << "\n\n Birth:                    " << p.birth_dateMar.date
         << "\n Death:                    " << p.death_dateMarEnd.date
         << "\n\n Father:                   " << dad_hus
         << "\n Mother:                   " << mom_wife
         << "\n\n Latest Marriage:          " << latestMar_ << isDivorced
         << "\n Latest Child:             " << latestChild_
         << "\n\n Previous Child of father: " << prevChildOfDad_
         << "\n Previous Child of mother: " << prevChildOfMom_
         << "\n\n\n ";
    system("pause");
}

void familyTree::printAll()
{
    inOrder(root);
}

int familyTree::countNodes()
{
    return countNodes(root);
}

int familyTree::countLeaf()
{
    return countLeaf(root);
}

int familyTree::maxHeight()
{
    int h=maxHeight(root);
    if(h>-1)
        return h;
    return 0;

}

void familyTree::Relation_Child(string name)
{
    if(isExistName(name)==false)
    {
        cout << "\n >>> Information:\n\n Not Found." << endl;
        saving(1000);
        return;
    }
    system(relationColor);
    inOrder_Relation_Child(root,name);
    system(menuColor);
}

void familyTree::Relation_Husband(string name)
{
    if(isExistName(name)==false)
    {
        cout << "\n >>> Information:\n\n Not Found." << endl;
        saving(1000);
        return;
    }
    system(relationColor);
    Individual_Mar* r=findName_R(root,name);
    if(r==NULL)
    {
        cout << "\n >>> Information:\n\n Not Found." << endl;
        saving(1000);
    }
    else
        printOne(convertToIndividual_Mar(r->latestMar_->mom_wife));
    system(menuColor);
}

void familyTree::Relation_Wife(string name)
{
    if(isExistName(name)==false)
    {
        cout << "\n >>> Information:\n\n Not Found." << endl;
        saving(1000);
        return;
    }
    system(relationColor);
    Individual_Mar* r=findName_R(root,name);
    if(r==NULL)
    {
        cout << "\n >>> Information:\n\n Not Found." << endl;
        saving(1000);
    }
    else
        printOne(convertToIndividual_Mar(r->latestMar_->dad_hus));
    system(menuColor);
}

void familyTree::Relation_brother(string name,string par,string mom)
{
    if(isExistName(par)==false || isExistName(mom)==false)
    {
        cout << "\n >>> Information:\n\n Not Found." << endl;
        saving(1000);
        return;
    }
    system(relationColor);
    Individual_Mar* r1=findName_R(root,par);
    Individual_Mar* r2=findName_R(root,mom);
    if(r1==NULL && r2==NULL)
    {
        cout << "\n >>> Information:\n\n Not Found.\n\n " << endl;
        saving(1000);
        system(menuColor);
        return;
    }
    else if(r1==NULL)
    {
        inOrder_Relation_ChildExceptBoy(root,"",mom,name);
        system(menuColor);
        return;
    }
    else if(r2==NULL)
    {
        inOrder_Relation_ChildExceptBoy(root,par,"",name);
        system(menuColor);
        return;
    }
    inOrder_Relation_ChildExceptBoy(root,par,mom,name);
    system(menuColor);
}

void familyTree::Relation_sister(string name,string par,string mom)
{
    if(isExistName(par)==false || isExistName(mom)==false)
    {
        cout << "\n >>> Information:\n\n Not Found." << endl;
        saving(1000);
        return;
    }
    system(relationColor);
    Individual_Mar* r1=findName_R(root,par);
    Individual_Mar* r2=findName_R(root,mom);
    if(r1==NULL && r2==NULL)
    {
        cout << "\n >>> Information:\n\n Not Found.\n\n " << endl;
        saving(1000);
        system(menuColor);
        return;
    }
    else if(r1==NULL)
    {
        inOrder_Relation_ChildExceptGirl(root,"",mom,name);
        system(menuColor);
        return;
    }
    else if(r2==NULL)
    {
        inOrder_Relation_ChildExceptGirl(root,par,"",name);
        system(menuColor);
        return;
    }
    inOrder_Relation_ChildExceptGirl(root,par,mom,name);
    system(menuColor);
}

void familyTree::Relation_GrandFather(string name)
{
    if(isExistName(name)==false)
    {
        cout << "\n >>> Information:\n\n Not Found." << endl;
        saving(1000);
        return;
    }
    Individual_Mar* r=findName_R(root,name);
    Individual_Mar* g1=findGrandFather(r);
    Individual_Mar* g2=findGrandFather2nd(r);
    if(g1==NULL && g2==NULL)
    {
        cout << "\n >>> Information:\n\n Not Found." << endl;
        saving(1000);
        return;
    }
    system(relationColor);
    if(g1!=NULL)
        printOne(convertToIndividual_Mar(g1));
    if(g2!=NULL)
        printOne(convertToIndividual_Mar(g2));
    system(menuColor);
}

void familyTree::Relation_GrandMother(string name)
{
    if(isExistName(name)==false)
    {
        cout << "\n >>> Information:\n\n Not Found." << endl;
        saving(1000);
        return;
    }
    Individual_Mar* r=findName_R(root,name);
    Individual_Mar* g1=findGrandMother(r);
    Individual_Mar* g2=findGrandMother2nd(r);
    if(g1==NULL && g2==NULL)
    {
        cout << "\n >>> Information:\n\n Not Found." << endl;
        saving(1000);
        return;
    }
    system(relationColor);
    if(g1!=NULL)
        printOne(convertToIndividual_Mar(g1));
    if(g2!=NULL)
        printOne(convertToIndividual_Mar(g2));
    system(menuColor);
}

void familyTree::Relation_Ancestor(string name)
{
    if(isExistName(name)==false)
    {
        cout << "\n >>> Information:\n\n Not Found." << endl;
        saving(1000);
        return;
    }
    system(relationColor);
    Individual_Mar* p=findName_R(root,name);
    while(p->dad_hus!=NULL)
    {
        p=findFather(p);
        printOne(convertToIndividual_Mar(p));
    }
    system(menuColor);
}

void familyTree::Relation_Uncel(string name)
{
    if(isExistName(name)==false)
    {
        cout << "\n >>> Information:\n\n Not Found." << endl;
        saving(1000);
        return;
    }
    Individual_Mar* n=findName_R(root,name);
    Individual_Mar* r=n->dad_hus;
    if(r==NULL)
    {
        cout << "\n >>> Information:\n\n Not Found." << endl;
        saving(1000);
        return;
    }
    Individual_Mar* p=r->dad_hus;
    Individual_Mar* m=r->mom_wife;
    if(p==NULL && m==NULL)
    {
        cout << "\n >>> Information:\n\n Not Found." << endl;
        saving(1000);
        return;
    }
    Relation_brother(name,p->name,m->name);
}

void familyTree::Relation_Uncel_momBrother(string name)
{
    if(isExistName(name)==false)
    {
        cout << "\n >>> Information:\n\n Not Found." << endl;
        saving(1000);
        return;
    }
    Individual_Mar* n=findName_R(root,name);
    Individual_Mar* r=n->mom_wife;
    if(r==NULL)
    {
        cout << "\n >>> Information:\n\n Not Found." << endl;
        saving(1000);
        return;
    }
    Individual_Mar* p=r->dad_hus;
    Individual_Mar* m=r->mom_wife;
    if(p==NULL && m==NULL)
    {
        cout << "\n >>> Information:\n\n Not Found." << endl;
        saving(1000);
        return;
    }
    Relation_brother(name,p->name,m->name);
}

void familyTree::Relation_Aunt(string name)
{
    if(isExistName(name)==false)
    {
        cout << "\n >>> Information:\n\n Not Found." << endl;
        saving(1000);
        return;
    }
    Individual_Mar* n=findName_R(root,name);
    Individual_Mar* r=n->dad_hus;
    if(r==NULL)
    {
        cout << "\n >>> Information:\n\n Not Found." << endl;
        saving(1000);
        return;
    }
    Individual_Mar* p=r->dad_hus;
    Individual_Mar* m=r->mom_wife;
    if(p==NULL && m==NULL)
    {
        cout << "\n >>> Information:\n\n Not Found." << endl;
        saving(1000);
        return;
    }
    Relation_sister(name,p->name,m->name);
}
void familyTree::Relation_Aunt_momSister(string name)
{
    if(isExistName(name)==false)
    {
        cout << "\n >>> Information:\n\n Not Found." << endl;
        saving(1000);
        return;
    }
    Individual_Mar* n=findName_R(root,name);
    Individual_Mar* r=n->mom_wife;
    if(r==NULL)
    {
        cout << "\n >>> Information:\n\n Not Found." << endl;
        saving(1000);
        return;
    }
    Individual_Mar* p=r->dad_hus;
    Individual_Mar* m=r->mom_wife;
    if(p==NULL && m==NULL)
    {
        cout << "\n >>> Information:\n\n Not Found." << endl;
        saving(1000);
        return;
    }
    Relation_sister(name,p->name,m->name);
}

void familyTree::Relation_FatherOfWife(string name)
{
    if(isExistName(name)==false)
    {
        cout << "\n >>> Information:\n\n Not Found." << endl;
        saving(1000);
        return;
    }
    Individual_Mar* q=findName_R(root,name);
    if(q->sex_type!='M')
    {
        cout << "\n >>> Information:\n\n Not Found." << endl;
        saving(1000);
        return;
    }
    if(q->latestMar_==NULL)
    {
        cout << "\n >>> Information:\n\n Not Found." << endl;
        saving(1000);
        return;
    }
    if(q->latestMar_->mom_wife->dad_hus==NULL)
    {
        cout << "\n >>> Information:\n\n Not Found." << endl;
        saving(1000);
        return;
    }
    else
    {
        system(relationColor);
        printOne(convertToIndividual_Mar(q->latestMar_->mom_wife->dad_hus));
        system(menuColor);
    }
}

void familyTree::Relation_MotherOfWife(string name)
{
    if(isExistName(name)==false)
    {
        cout << "\n >>> Information:\n\n Not Found." << endl;
        saving(1000);
        return;
    }
    Individual_Mar* q=findName_R(root,name);
    if(q->sex_type!='M')
    {
        cout << "\n >>> Information:\n\n Not Found." << endl;
        saving(1000);
        return;
    }
    if(q->latestMar_==NULL)
    {
        cout << "\n >>> Information:\n\n Not Found." << endl;
        saving(1000);
        return;
    }
    if(q->latestMar_->mom_wife->mom_wife==NULL)
    {
        cout << "\n >>> Information:\n\n Not Found." << endl;
        saving(1000);
        return;
    }
    else
    {
        system(relationColor);
        printOne(convertToIndividual_Mar(q->latestMar_->mom_wife->mom_wife));
        system(menuColor);
    }
}
void familyTree::Relation_FatherOfHus(string name)
{
    if(isExistName(name)==false)
    {
        cout << "\n >>> Information:\n\n Not Found." << endl;
        saving(1000);
        return;
    }
    Individual_Mar* q=findName_R(root,name);
    if(q->sex_type!='F')
    {
        cout << "\n >>> Information:\n\n Not Found." << endl;
        saving(1000);
        return;
    }
    if(q->latestMar_==NULL)
    {
        cout << "\n >>> Information:\n\n Not Found." << endl;
        saving(1000);
        return;
    }
    if(q->latestMar_->dad_hus->dad_hus==NULL)
    {
        cout << "\n >>> Information:\n\n Not Found." << endl;
        saving(1000);
        return;
    }
    else
    {
        system(relationColor);
        printOne(convertToIndividual_Mar(q->latestMar_->dad_hus->dad_hus));
        system(menuColor);
    }
}
void familyTree::Relation_MotherOfHus(string name)
{
    if(isExistName(name)==false)
    {
        cout << "\n >>> Information:\n\n Not Found." << endl;
        saving(1000);
        return;
    }
    Individual_Mar* q=findName_R(root,name);
    if(q->sex_type!='F')
    {
        cout << "\n >>> Information:\n\n Not Found." << endl;
        saving(1000);
        return;
    }
    if(q->latestMar_==NULL)
    {
        cout << "\n >>> Information:\n\n Not Found." << endl;
        saving(1000);
        return;
    }
    if(q->latestMar_->dad_hus->mom_wife==NULL)
    {
        cout << "\n >>> Information:\n\n Not Found." << endl;
        saving(1000);
        return;
    }
    else
    {
        system(relationColor);
        printOne(convertToIndividual_Mar(q->latestMar_->dad_hus->mom_wife));
        system(menuColor);
    }
}

void familyTree::Relation_Bajenagh(string name)
{
    if(isExistName(name)==false)
    {
        cout << "\n >>> Information:\n\n Not Found." << endl;
        saving(1000);
        return;
    }
    Individual_Mar* q=findName_R(root,name);
    if(q->sex_type!='M')
    {
        cout << "\n >>> Information:\n\n Not Found." << endl;
        saving(1000);
        return;
    }
    if(q->latestMar_==NULL)
    {
        cout << "\n >>> Information:\n\n Not Found." << endl;
        saving(1000);
        return;
    }
    if(q->latestMar_->mom_wife->dad_hus==NULL || q->latestMar_->mom_wife->mom_wife==NULL)
    {
        cout << "\n >>> Information:\n\n Not Found." << endl;
        saving(1000);
        return;
    }
    else
    {
        system(relationColor);
        Relation_sister_ForBajenagh(q->latestMar_->mom_wife->name,q->latestMar_->mom_wife->dad_hus->name,q->latestMar_->mom_wife->mom_wife->name);
        system(menuColor);
    }
}

void familyTree::Relation_Descendent(string name)
{
    if(isExistName(name)==false)
    {
        cout << "\n >>> Information:\n\n Not Found." << endl;
        saving(1000);
        return;
    }
    system(relationColor);
    Individual_Mar* q=findName_R(root,name);
    inOrder_Relation_Descendent(name,root);
    system(menuColor);
}

void familyTree::Relation_betweenPeople(string a,string b)
{
    Individual_Mar* x=findName_R(root,a);
    Individual_Mar* y=findName_R(root,b);
    if(x==NULL && y==NULL)
    {
        cout << "\n >>> Information:\n\n '" << a << "' and '" << b << "' Not Found." << endl;
        saving(1500);
        return;
    }
    else if(x==NULL)
    {
        cout << "\n >>> Information:\n\n '" << a << "' Not Found." << endl;
        saving(1500);
        return;
    }
    else if(y==NULL)
    {
        cout << "\n >>> Information:\n\n '" << b << "' Not Found." << endl;
        saving(1500);
        return;
    }
    //What is the relationship between a and b?
    system(relationColor);
    string relationship="Unknown!";

    if(x->dad_hus!=NULL && x->dad_hus==y)
    {
        if(x->sex_type=='M')
            relationship="Son";
        else
            relationship="Girl";
    }
    else if(x==findFather(y))
        relationship="Father";
    else if(x==findMother(y))
        relationship="Mother";
    else if(x->latestMar_!=NULL && x->latestMar_->dad_hus==y)
        relationship="Wife";
    else if(x->latestMar_!=NULL && x->latestMar_->mom_wife==y)
        relationship="Husband";
    else if(findFather(x)==findFather(y) && findMother(x)==findMother(y) && findFather(x)!=NULL && findMother(x)!=NULL)
    {
        if(x->sex_type=='M')
            relationship="Brother";
        else
            relationship="Sister";
    }
    else if(x==findGrandFather(y) || x==findGrandFather2nd(y))
        relationship="Grand Father";
    else if(x==findGrandMother(y) || x==findGrandMother2nd(y))
        relationship="Grand Mother";
    else if(y==findGrandFather(x) || y==findGrandFather2nd(x))
        relationship="Descendent";
    else if(y==findGrandMother(x) || y==findGrandMother2nd(x))
        relationship="Descendent";
    else if(isAncestorXY(x,y)==true)
        relationship="member of Ancestors";
    else if(isDescendentXY(x,y)==true)
        relationship="member of Descendents";

    cout << "\n >>> Information:\n\n The Relationship of '" << a << "' with '" << b << "' is " << relationship << "\n\n ";
    system("pause");
    system(menuColor);
}
