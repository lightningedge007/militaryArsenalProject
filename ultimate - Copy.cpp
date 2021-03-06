#include<bits/stdc++.h>
using namespace std;
//For a disconnected undirected graph, an articulation point is a vertex removing which increases number of connected components.
static int flow=0;
static int minCapacity=INT_MAX;

int hasPath(string v1name,string v2name,int mCap,map<string,map<string,int> > &dag,map<string,bool> &processed)
{
    processed[v1name]=true;

    if(v1name==v2name)
    {
        flow+=mCap;
        return mCap;
    }

    map<string,int> nbrs=dag[v1name];
    map<string,int>::iterator mi;
    map<string,int>::iterator mi2;

    for(mi=nbrs.begin();mi!=nbrs.end();mi++)
    {
        if(processed.find(mi->first)==processed.end() && dag[v1name][mi->first]>0)
        {


            int cap=dag[v1name][mi->first];
            int revcap=dag[mi->first][v1name];
            int localMCap=hasPath(mi->first,v2name,min(cap,mCap),dag,processed);

            if(localMCap!=-1)
                {
                dag[v1name][mi->first]=cap-localMCap;
                dag[mi->first][v1name]=revcap+localMCap;
                return localMCap;
            }


        }
    }

    return -1;
}


class bridge
{
public:

    int a;
    int b;
};

class ArticulationPair
{
    public:

    int vert;
    int disc;
    int low;
    bool isAP;
    bool processed;
    int parent=-1;
};

void DFT2(int time,int currv,int **graph,ArticulationPair *result[],int n,vector<bridge> &bv)
{
    result[currv]->processed=true;
    result[currv]->disc=result[currv]->low=time;

    int rootChildCounter=0;

    for(int i=0;i<n;i++)
    {
        if(graph[currv][i]!=1)
        {
            continue;
        }

        if(result[i]->processed==false)
        {

            result[i]->parent=currv;
            DFT2(time+1,i,graph,result,n,bv);
            result[currv]->low=min(result[currv]->low,result[i]->low);


                if(result[currv]->disc<result[i]->low)
                {
                    bridge br;
                    br.a=currv;
                    br.b=i;
                    bv.push_back(br);

                }



        }
        else if(result[currv]->parent!=i)
        {
            result[currv]->low=min(result[currv]->low,result[i]->disc);
        }

    }

}
void DFT(int time,int currv,int **graph,ArticulationPair *result[],int n)
{
    result[currv]->processed=true;
    result[currv]->disc=time;
    result[currv]->low=time;

    int rootChildCounter=0;

    for(int i=0;i<n;i++)
    {
        if(graph[currv][i]!=1)
        {
            continue;
        }

        if(result[i]->processed==false)
        {
            rootChildCounter++;
            result[i]->parent=currv;
            DFT(time+1,i,graph,result,n);
            result[currv]->low=min(result[currv]->low,result[i]->low);

            if(result[currv]->parent!=-1)
            {
                if(result[currv]->disc<=result[i]->low)
                {
                    result[currv]->isAP=new bool;
                    result[currv]->isAP=true;
                }
            }
            else
            {
                if(rootChildCounter > 1)
                {
                    result[currv]->isAP=new bool;
                    result[currv]->isAP=true;
                }
            }

        }
        else if(result[currv]->parent!=i)
        {
            result[currv]->low=min(result[currv]->low,result[i]->disc);
        }

    }

}


int main()
{
    cout<<"\n\n-------WELCOME TO GRIM REAPER ADVANCED MILITARY ARSENAL! (GRAMA V_1.1)---------\n\n"<<endl;
    cout<<"\nWHICH COUNTRIES DO YOU WANT TO DESTROY ? \n"<<endl;
    string s;
    cin>>s;
    cout<<"\nANALYSING COUTRIES' WEAKSPOTS .......\n.............."<<endl;

    map<int,string> china;
    china[0]="qingdao";
    china[1]="beijing";
    china[2]="shanghai";
    china[3]="hangzhou";
    china[4]="guangzhou";
    china[5]="xian";
    china[6]="tianjin";
    china[7]="chengdu";
    china[8]="shenzen";
    china[9]="wuhan";
    china[10]="suzhou";
    china[11]="nanjing";
    china[12]="shenyang";
    china[13]="zhengzhou";
    china[14]="changsa";


    map<int,string> pakistan;
    pakistan[0]="quetta";
    pakistan[1]="lahore";
    pakistan[2]="karachi";
    pakistan[3]="faisalabad";
    pakistan[4]="peshawar";
    pakistan[5]="multan";
    pakistan[6]="islamabad";
    pakistan[7]="hyderabad";
    pakistan[8]="rawalpindi";
    pakistan[9]="sialkot";
    pakistan[11]="bahawalpur";
    pakistan[12]="sargodha";
    pakistan[13]="abbotabad";
    pakistan[14]="sukkur";
    pakistan[10]="kotli";

    map<string,map<string,int> > chinaroads;
    chinaroads[china[9]][china[5]]=5000;

    chinaroads[china[0]][china[1]]=5000;
    chinaroads[china[1]][china[2]]=1110;
    chinaroads[china[2]][china[9]]=800;
    chinaroads[china[0]][china[7]]=7000;
    chinaroads[china[8]][china[9]]=940;
    chinaroads[china[7]][china[8]]=660;
    chinaroads[china[9]][china[10]]=1030;
    chinaroads[china[9]][china[4]]=1011;
    chinaroads[china[3]][china[9]]=770;
    chinaroads[china[5]][china[13]]=998;
    chinaroads[china[14]][china[13]]=808;
    chinaroads[china[6]][china[13]]=997;
    chinaroads[china[10]][china[11]]=2000;
    chinaroads[china[11]][china[12]]=2020;
    chinaroads[china[12]][china[13]]=2002;
        chinaroads[china[5]][china[9]]=0;


    chinaroads[china[1]][china[0]]=0;
    chinaroads[china[2]][china[1]]=0;
    chinaroads[china[9]][china[2]]=0;
    chinaroads[china[7]][china[0]]=0;
    chinaroads[china[9]][china[8]]=0;
    chinaroads[china[8]][china[7]]=0;
    chinaroads[china[10]][china[9]]=0;
    chinaroads[china[4]][china[9]]=0;
    chinaroads[china[9]][china[3]]=0;
    chinaroads[china[13]][china[5]]=0;
    chinaroads[china[13]][china[14]]=0;
    chinaroads[china[13]][china[6]]=0;
    chinaroads[china[11]][china[10]]=0;
    chinaroads[china[12]][china[11]]=0;
    chinaroads[china[13]][china[12]]=0;


    map<string,map<string,int> > pakistanroads;


    pakistanroads[pakistan[0]][pakistan[1]]=300;
    pakistanroads[pakistan[1]][pakistan[2]]=111;
    pakistanroads[pakistan[2]][pakistan[9]]=80;
    pakistanroads[pakistan[0]][pakistan[7]]=400;
    pakistanroads[pakistan[8]][pakistan[9]]=94;
    pakistanroads[pakistan[7]][pakistan[8]]=66;
    pakistanroads[pakistan[9]][pakistan[10]]=103;
    pakistanroads[pakistan[9]][pakistan[4]]=101;

    pakistanroads[pakistan[3]][pakistan[9]]=77;
    pakistanroads[pakistan[5]][pakistan[13]]=99;
    pakistanroads[pakistan[14]][pakistan[13]]=80;
    pakistanroads[pakistan[6]][pakistan[13]]=97;
    pakistanroads[pakistan[10]][pakistan[11]]=201;
    pakistanroads[pakistan[11]][pakistan[12]]=202;
    pakistanroads[pakistan[12]][pakistan[13]]=200;



    pakistanroads[pakistan[1]][pakistan[0]]=0;
    pakistanroads[pakistan[2]][pakistan[1]]=0;
    pakistanroads[pakistan[9]][pakistan[2]]=0;
    pakistanroads[pakistan[7]][pakistan[0]]=0;
    pakistanroads[pakistan[9]][pakistan[8]]=0;
    pakistanroads[pakistan[8]][pakistan[7]]=0;
    pakistanroads[pakistan[10]][pakistan[9]]=0;
    pakistanroads[pakistan[4]][pakistan[9]]=0;

    pakistanroads[pakistan[9]][pakistan[3]]=0;
    pakistanroads[pakistan[13]][pakistan[5]]=0;
    pakistanroads[pakistan[13]][pakistan[14]]=0;
    pakistanroads[pakistan[13]][pakistan[6]]=0;
    pakistanroads[pakistan[11]][pakistan[10]]=0;
    pakistanroads[pakistan[12]][pakistan[11]]=0;
    pakistanroads[pakistan[13]][pakistan[12]]=0;


    cout<<"\nCALCULATING MAXIMUM AMMUNIATIONS, OIL AND GOODS TRANSFER THROUGHOUT THE ENEMY COUNTRIES ........\n............\n\n"<<endl;
    //ford fulkerson
    while(true)
    {
        //processed=new map();
        map<string,bool> processed;
        int localMCap=hasPath(china[0],china[13],INT_MAX,chinaroads,processed);
        if(localMCap==-1)
        {
            break;
        }
    }

    cout<<flow;
    cout<<" MILLION TONS OF CARGO TRANSFERRABLE VIA CHINA\n\n\n";

    flow=0;

    while(true)
    {
        //processed=new map();
        map<string,bool> processed;
        int localMCap=hasPath(pakistan[0],pakistan[13],INT_MAX,pakistanroads,processed);
        if(localMCap==-1)
        {
            break;
        }
    }


    cout<<flow;
    cout<<" MILLION TONS OF CARGO TRANSFERRABLE VIA PAKISTAN\n\n\n";


    int n=15;
    int **graph_china=new int*[n];
    int **graph_pakistan=new int*[n];

    for(int i=0;i<n;i++){
        graph_china[i]=new int[n];
        graph_pakistan[i]=new int[n];
    }
    ArticulationPair *result_china[n];
    ArticulationPair *result_pakistan[n];

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(chinaroads[china[i]][china[j]]>0){
                graph_china[i][j]=1;
                graph_china[j][i]=1;
            }
            if(pakistanroads[pakistan[i]][pakistan[j]]>0){
                graph_pakistan[i][j]=1;
                graph_pakistan[j][i]=1;
            }
        }
    }



    for(int i=0;i<n;i++)
    {
        result_china[i]=new ArticulationPair;
        result_pakistan[i]=new ArticulationPair;
        result_china[i]->vert=i;
        result_pakistan[i]->vert=i;
    }

    for(int i=0;i<n;i++)
    {
        if(result_china[i]->processed==true){
            continue;
        }
        DFT(0,i,graph_china,result_china,n);
    }

    cout<<"\nFOLLOWING IS A LIST OF ALL CHINESE CITIES WHO HOLD NUCLEAR WEAPONS\n"<<endl;

    vector<string> ap_c;
   for(int i=0;i<n;i++)
    {
        int t=result_china[i]->vert;
        cout<<china[t]<<" --> "<<result_china[i]->isAP<<endl;
        cout<<endl;
        if(result_china[i]->isAP==true)
        {
            ap_c.push_back(china[result_china[i]->vert]);
        }
    }

    cout<<"\nFOLLOWING CITIES MUST BE DESTROYED IN ORDER TO PREVENT TRANSFER OF GOODS THROUGHOUT CHINA\n"<<endl;
    for(int i=0;i<ap_c.size();i++){
        cout<<ap_c.at(i)<<"\n\n";
    }



    cout<<endl;

    for(int i=0;i<n;i++)
    {
        if(result_pakistan[i]->processed==true){
            continue;
        }
        DFT(0,i,graph_pakistan,result_pakistan,n);
    }

    cout<<"\nFOLLOWING IS A LIST OF ALL PAKISTANI CITIES WHO HOLD NUCLEAR WEAPONS\n"<<endl;

    vector<string> ap_p;
   for(int i=0;i<n;i++)
    {
        int t=result_pakistan[i]->vert;
        cout<<pakistan[t]<<" --> "<<result_pakistan[i]->isAP<<endl;
        cout<<endl;
        if(result_pakistan[i]->isAP==true)
        {
            ap_p.push_back(pakistan[result_pakistan[i]->vert]);
        }
    }
    cout<<"\nFOLLOWING CITIES MUST BE DESTROYED IN ORDER TO PREVENT TRANSFER OF GOODS THROUGHOUT PAKISTAN\n"<<endl;

    for(int i=0;i<ap_p.size();i++){
        cout<<ap_p.at(i)<<"\n\n";
    }
    cout<<endl;


    ArticulationPair *result2_c[n];
    ArticulationPair *result2_p[n];

    vector<bridge> bv_c;
    vector<bridge> bv_p;

    for(int i=0;i<n;i++)
    {
        result2_c[i]=new ArticulationPair;
        result2_p[i]=new ArticulationPair;
        result2_c[i]->vert=i;
        result2_p[i]->vert=i;
    }

    for(int i=0;i<n;i++)
    {
        if(result2_c[i]->processed==true){
            continue;
        }
        DFT2(0,i,graph_china,result2_c,n,bv_c);
    }

    for(int i=0;i<n;i++)
    {
        if(result2_p[i]->processed==true){
            continue;
        }
        DFT2(0,i,graph_pakistan,result2_p,n,bv_p);
    }

    vector<int> ap2_c;
   for(int i=0;i<n;i++)
    {
        //cout<<result[i]->vert<<" --> "<<result[i]->isAP<<endl;
        if(result2_c[i]->isAP==true)
        {
            ap2_c.push_back(result2_c[i]->vert);
        }
    }

    vector<int> ap2_p;
   for(int i=0;i<n;i++)
    {
        //cout<<result[i]->vert<<" --> "<<result[i]->isAP<<endl;
        if(result2_p[i]->isAP==true)
        {
            ap2_p.push_back(result2_p[i]->vert);
        }
    }


    cout<<"\nFOLLOWING ROADS MUST BE DESTROYED IN ORDER TO PREVENT TRANSFER OF GOODS THROUGHOUT CHINA\n"<<endl;

    vector<bridge>::iterator vi;
    for(vi=bv_c.begin();vi!=bv_c.end();vi++)
    {
        cout<<china[(*vi).a]<<"--"<<china[(*vi).b]<<endl;
        cout<<endl;
    }

    cout<<"\nFOLLOWING ROADS MUST BE DESTROYED IN ORDER TO PREVENT TRANSFER OF GOODS THROUGHOUT PAKISTAN\n"<<endl;

    vector<bridge>::iterator vin;
    for(vin=bv_p.begin();vin!=bv_p.end();vin++)
    {
        cout<<pakistan[(*vin).a]<<"--"<<pakistan[(*vin).b]<<endl;
                cout<<endl;

    }

    cout<<"\n\n\n\nChina has low articulation points and bridges because destroying\n";
     cout<<"any one of them disconnects the country's network and such vulnerabilities must be kept as low as possible!!\n";
     cout<<"On the other hand Pakistan is full of vulnerable targets to disrupt the country's network!!\n\n\n"<<endl;

    return 0;
}
