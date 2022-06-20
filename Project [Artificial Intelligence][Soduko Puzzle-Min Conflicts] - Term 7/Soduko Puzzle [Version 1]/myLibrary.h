class repeatDetection
{
    private:
        bool flags[10]; //FLAGS[0] FOR DETECTION

    public:
        repeatDetection();
        void set(const char input); // INPUT={1,2,3, ... ,9}
        void reset();
        bool isRepeated(){return flags[0];}
};

repeatDetection::repeatDetection()
{
    for(char i=0;i<10;i++)
        flags[i]=false;
}

void repeatDetection::set(const char input)
{
    if(flags[input])
        flags[0]=true;
    else
        flags[input]=true;
}

void repeatDetection::reset()
{
    for(char i=0;i<10;i++)
        flags[i]=false;
}

////////////////////////////////////////////////////////////////////////////////

class repeatCounter
{
    private:
        char cnt[10];

    public:
        repeatCounter();
        void inc(const char input){++cnt[input];}
        void reset();
        char get(const char input){return cnt[input];}
        char minimum();
};

repeatCounter::repeatCounter()
{
    for(char i=0;i<10;i++)
        cnt[i]=0;
}

void repeatCounter::reset()
{
    for(char i=0;i<10;i++)
        cnt[i]=0;
}

char repeatCounter::minimum()
{
    char min_index=1;
    for(char i=2;i<10;i++)
        if(cnt[i]<cnt[min_index])
            min_index=i;
    return min_index;
}
