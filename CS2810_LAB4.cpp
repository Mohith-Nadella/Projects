#include<bits/stdc++.h>
using namespace std;
class QNS{
    private:
    int P,D,E,H;
    public:
    QNS(){
        P=1000;
        D=500;
        E=300;
        H=0;
    }
    QNS(int p,int d,int e,int h){
        P=p;
        if(P>5000)
        P=5000;
        D=d;
        E=e;
        H=h;
        if(H<0)
        H=0;
    }
    QNS(const QNS& suit1){
        P=suit1.P;
        D=suit1.D;
        E=suit1.E;
        H=suit1.H;
    }
    void operator+(const QNS& suit){
        P+=suit.E;
        D+=suit.D;
        E+=suit.P;
        if(P>5000)
        P=5000;
    }
    void operator-(int x){
        D-=x;
        E+=x;
        H+=x;
    }
    void operator*(int x){
        P+=((P*x)/100);
        E+=5*x;
        H+=x;
        if(P>5000)
        P=5000;
    }
    void operator/(int x){
        D+=x;
        H-=x;
        if(H<0)
        H=0;
    }
    void boostPower(int factor){
        (*this)*factor;
    }
    void boostPower(QNS otherSuit){
        (*this)+otherSuit;
    }
    bool operator==(QNS otherSuit){
        return (P==otherSuit.P)&&(D==otherSuit.D);
    }
    bool operator<(QNS otherSuit){
        return (P+D)<(otherSuit.P+otherSuit.D);
    }
    int get_P(){
        return P;
    }
    int get_D(){
        return D;
    }
    int get_E(){
        return E;
    }
    int get_H(){
        return H;
    }
    void set_P(int x){
        P=x;
    }
    void set_D(int x){
        D=x;
    }
    void set_E(int x){
        E=x;
    }
    void set_H(int x){
        H=x;
    }
};
queue<QNS> suits;
class Avenger{
    private:
    string name;
    QNS suit;
    int attackStrength;
    public:
    Avenger(){}
    Avenger(string avName,QNS avSuit,int strength){
        name=avName;
        suit=avSuit;
        attackStrength=strength;
    }
    void attack(Avenger& enemy){
        enemy.suit-attackStrength;
    }
    bool upgradeSuit_bool(){
        if(suits.empty()){
            return false;
        }
        return true;
    }
    void upgradeSuit(){
        suit+suits.front();
        suits.pop();
    }
    void repair(int x){
        suit/x;
    }
    void printStatus(){
        cout<<name<<" "<<suit.get_P()<<" "<<suit.get_D()<<" "<<suit.get_E()<<" "<<suit.get_H()<<endl;
    }
    string get_name(){
        return name;
    }
    QNS& get_suit(){
        return suit;
    }
};
class Battle{
    private:
    vector<Avenger> heroes;
    vector<Avenger> enemies;
    vector<string> battleLog;
    map<string,int> hero_map;
    map<string,int> enemy_map;
    public:
    Battle(){}
    void add_hero(Avenger& hero){
        heroes.push_back(hero);
        hero_map[hero.get_name()]=heroes.size()-1;
    }
    void add_enemy(Avenger& enemy){
        enemies.push_back(enemy);
        enemy_map[enemy.get_name()]=enemies.size()-1;
    }
    void printBattleLog(){
        for(int i=0;i<(int)battleLog.size();i++){
            cout<<battleLog[i]<<endl;
        }
    }
    int Result(){
        int numsH=0;
        int numsE=0;
        for(int i=0;i<(int)heroes.size();i++){
            if(heroes[i].get_suit().get_D()>0)
            numsH+=heroes[i].get_suit().get_P()+heroes[i].get_suit().get_D();
        }
        for(int i=0;i<(int)enemies.size();i++){
            if(enemies[i].get_suit().get_D()>0)
            numsE+=enemies[i].get_suit().get_P()+enemies[i].get_suit().get_D();
        }
        if(numsH>numsE){
            return 1;
        }else if(numsH<numsE){
            return -1;
        }else{
            return 0;
        }
    }
    void startBattle(){
        string s;
        cin>>s;
        while(s!="End"){
            if(s=="Attack"){
                string s1,s2;
                cin>>s1>>s2;
                if((hero_map.find(s1)==hero_map.end()&&enemy_map.find(s1)==enemy_map.end())||(hero_map.find(s2)==hero_map.end()&&enemy_map.find(s2)==enemy_map.end())){
                    continue;
                }
                Avenger* S1;
                Avenger* S2;
                if(hero_map.find(s1)!=hero_map.end()){
                    S1=&heroes[hero_map[s1]];
                }else{
                    S1=&enemies[enemy_map[s1]];
                }
                if(hero_map.find(s2)!=hero_map.end()){
                    S2=&heroes[hero_map[s2]];
                }else{  
                    S2=&enemies[enemy_map[s2]];
                }
                S1->attack(*S2);
                battleLog.push_back(s1+" attacks "+s2);
                if(S2->get_suit().get_D()<=0){
                    battleLog.push_back(s2+" suit destroyed");
                }else if(S2->get_suit().get_H()>500){
                    battleLog.push_back(s2+" suit overheated");
                }
            }else if(s=="Repair"){
                string s1;
                int x;
                cin>>s1>>x;
                if(hero_map.find(s1)!=hero_map.end()){
                    heroes[hero_map[s1]].repair(x);
                    battleLog.push_back(s1+" repaired");
                }else if(enemy_map.find(s1)!=enemy_map.end()){
                    enemies[enemy_map[s1]].repair(x);
                    battleLog.push_back(s1+" repaired");
                }
            }else if(s=="BoostPowerByFactor"){
                string s1;
                int x;
                cin>>s1>>x;
                if(hero_map.find(s1)!=hero_map.end()){
                    heroes[hero_map[s1]].get_suit().boostPower(x);
                    battleLog.push_back(s1+" boosted");
                    if(heroes[hero_map[s1]].get_suit().get_H()>500){
                        battleLog.push_back(s1+" suit overheated");
                    }
                }else if(enemy_map.find(s1)!=enemy_map.end()){
                    enemies[enemy_map[s1]].get_suit().boostPower(x);
                    battleLog.push_back(s1+" boosted");
                    if(enemies[enemy_map[s1]].get_suit().get_H()>500){
                        battleLog.push_back(s1+" suit overheated");
                    }
                }
            }else if(s=="BoostPower"){
                string s1;
                int p,d,e,h;
                cin>>s1>>p>>d>>e>>h;
                if(hero_map.find(s1)!=hero_map.end()){
                    QNS new_suit(p,d,e,h);
                    heroes[hero_map[s1]].get_suit().boostPower(new_suit);
                    battleLog.push_back(s1+" boosted");
                }else if(enemy_map.find(s1)!=enemy_map.end()){
                    QNS new_suit(p,d,e,h);
                    enemies[enemy_map[s1]].get_suit().boostPower(new_suit);
                    battleLog.push_back(s1+" boosted");
                }
            }else if(s=="Upgrade"){
                string s1;
                cin>>s1;
                if(hero_map.find(s1)!=hero_map.end()){
                    if(heroes[hero_map[s1]].upgradeSuit_bool()){
                        heroes[hero_map[s1]].upgradeSuit();
                        battleLog.push_back(s1+" upgraded");
                    }else{
                        battleLog.push_back(s1+" upgrade Fail");
                    }
                }else if(enemy_map.find(s1)!=enemy_map.end()){
                    if(enemies[enemy_map[s1]].upgradeSuit_bool()){
                        enemies[enemy_map[s1]].upgradeSuit();
                        battleLog.push_back(s1+" upgraded");
                    }else{
                        battleLog.push_back(s1+" upgrade Fail");
                    }
                }
            }else if(s=="AvengerStatus"){
                string s1;
                cin>>s1;
                if(hero_map.find(s1)!=hero_map.end()){
                    heroes[hero_map[s1]].printStatus();
                }else if(enemy_map.find(s1)!=enemy_map.end()){
                    enemies[enemy_map[s1]].printStatus();
                }
            }else if(s=="PrintBattleLog"){
                printBattleLog();
            }else if(s=="BattleStatus"){
                if(Result()==1){
                    cout<<"heroes are winning"<<endl;
                }else if(Result()==-1){
                    cout<<"enemies are winning"<<endl;
                }else{
                    cout<<"tie"<<endl;
                }
            }
            cin>>s;
        }
    }
};
int main(){
    int k,n,m;
    cin>>k>>n>>m;
    Battle b;
    for(int i=0;i<k;i++){
        int p,d,e,h;
        cin>>p>>d>>e>>h;
        QNS suit(p,d,e,h);
        suits.push(suit);
    }
    for(int i=0;i<n;i++){
        string name;
        int aS;
        cin>>name>>aS;
        if(suits.empty()){
            cout<<name<<" is out of fight"<<endl;
            continue;
        }
        Avenger a(name,suits.front(),aS);
        b.add_hero(a);
        suits.pop();
    }
    for(int i=0;i<m;i++){
        string name;
        int aS;
        cin>>name>>aS;
        if(suits.empty()){
            cout<<name<<" is out of fight"<<endl;
            continue;
        }
        Avenger e(name,suits.front(),aS);
        b.add_enemy(e);
        suits.pop();
    }
    string s;
    cin>>s;
    b.startBattle();
}
