#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;
// 1..
enum struct Frequency {  
    once = 1,
    daily = 365,
    weekly = 52,
    monthly = 12
};
ostream& operator<<(ostream& out, const Frequency& f){
    switch (f)
    {
    case Frequency::daily:
        return out<<"daily ";
        break;
    case Frequency::weekly:
        return out<<"weekly ";
        break;
    case Frequency::monthly:
        return out<<"monthly ";
        break;
    default:
        break;
    }
    return out;
}
istream& operator>>(istream& in, Frequency& in_f){
    char c;
    cout<<"(o) once\n(d) daily\n(m) monthly\n(w) weekly\n";
    cout<<"your choice: ";
    in>>c;
    if(c == 'o'){
        in_f = Frequency::once;
    }
    else if(c == 'd'){
        in_f = Frequency::daily;
    }
    else if (c == 'm')
    {   
        in_f = Frequency::monthly;
    }
    else if (c == 'w')
    {
        in_f = Frequency::weekly;
    }
    return in;
};
// 2..
class CO2Emission 
{
private:
    CO2Emission* next;
public:
    CO2Emission (): next(NULL) {}
    CO2Emission* get_next(){
        return next;
    }
    void set_next(CO2Emission* nxt){
        next = nxt;
    }
    virtual float get_co2() = 0;
    virtual void print() = 0;
    virtual ~CO2Emission () {
        cout<<"destructor CO2Emission: done"<<endl;
    }
};
// add 1..
class Power : public CO2Emission
{
private:
    float kWh;
    virtual float get_co2_kWh() = 0;
public:
    Power(){
        cout<<"power data input kilo Watt hours: ";
        cin>>kWh;
    }
    Power(float kW) : kWh(kW) {}
    float get_co2(){
        float res = kWh * get_co2_kWh();
        return res;
    }
    void print(){
        cout<<"power "<<fixed <<setprecision(1) <<kWh<<" kWh ("<<
        fixed <<setprecision(3)<<get_co2_kWh() <<" kg CO2/kWh ) "<<
        fixed <<setprecision(1) <<get_co2() <<" kg CO2"<<endl;
    }
    virtual ~Power(){
        cout<<"  destructor Power: "<<kWh <<" kWh done"<<endl;
    }
};

// 3..
class Transport : public CO2Emission
{
private:
    float km ;
    Frequency frequency;
    virtual float get_co2_pkm() = 0;
public:
    Transport (){
        cout<<"transport distance kilometers: ";
        cin>>km;
        cout<<"frequency input:"<<endl;
        cin>>frequency;
    }
    Transport(float k, Frequency fre = Frequency::once) : km(k), frequency(fre) {}
    float get_co2(){
        float em_pkm = get_co2_pkm();
        float result = float(frequency) * em_pkm * km ;
        return result;
    }
    void print(){
        cout<<"transport "<< frequency << fixed << setprecision(1)<<km<<" km ";
        cout<<"("<< fixed << setprecision(3) <<get_co2_pkm() <<" kg CO2/pkm) ";
        cout<<fixed << setprecision(1) <<get_co2() <<" kg CO2"<<endl;
    }
    virtual ~Transport (){
        cout<<"  destructor Transport: "<<frequency<<" "<<km<<" km done"<<endl;
    }
};
// 4..
class Bus : public Transport
{
private:
    bool local_transport;
    float get_co2_pkm(){
        if (local_transport == true){
            return 0.111;
        }
        else {
            return 0.036;
        }
    }
public:
    Bus(){
        int c;
        cout<<"(1) local transport bus"<<"\n"<<"(2) long distance bus"<<endl;
        cout<<"your choice: ";
        cin>>c;
        if( c == 1)
            local_transport = true;
        else local_transport = false;
        
    }
    Bus(bool l, float k) : local_transport(l), Transport(k) { }
    void print(){
        string res = local_transport ? "local bus " : "long distance bus ";
        cout<< res;
        Transport::print();
    }
    ~Bus(){
        cout<<"    destructor Bus: ";
        print();
    }
};
// 5..
class Car : public Transport
{
private: 
    float l_fuel_km ;
    float get_co2_pkm () {
        float em_per_100km = 2.3;
        float em_per_1km = (em_per_100km/100) * l_fuel_km;
        return em_per_1km;
    }
public: 
    Car(){
        cout<< "passenger car consumption liter petrol per 100 kilometers: ";
        cin>> l_fuel_km;
       
    }
    Car(float f, float k) : l_fuel_km(f), Transport(k) {}
    void print(){
        cout<< "passenger car ";
        Transport::print();
    }
    ~Car() { 
        cout<<"    destructor Car: ";
        print();
    }
};
// 6..
class Flight : public Transport 
{
private:
    float get_co2_pkm() {
        return 0.27 ;
    }
public:
    Flight() {}
    Flight(float k) : Transport(k) {}
    
    void print() {
        cout<< "flight ";
        Transport::print();
    }
    ~Flight () {
        cout<<"    destructor Flight: done"<<endl;
    }
};
// 7..
class Train : public Transport
{
private:
    bool local_transport, one_way ;
    float get_co2_pkm(){
     if (local_transport == true){
            return 0.085 ;
        }
        else {
            return 0.035 ;
        }   
    }
public:
    Train () {
        int c, b;
        cout<<"(1) local transport train"<<'\n'<<"(2) long distance train"<<endl;
        cout<<"your choice: ";
        cin>>c;
        cout<<"(1) one-way"<<'\n'<<"(2) return"<<endl;
        cout<<"your choice: ";
        cin>>b;
        if( c == 1)
            local_transport = true;
        else 
            local_transport = false;
        if( b == 1)
            one_way = true;
        else 
            one_way = false;
    }
    Train(bool t, float k, bool w = true) : Transport(k), local_transport(t), one_way(w) {}
    float get_co2(){
        float em = Transport::get_co2();
        if(one_way == true)
            return em ;
        
        else 
            return 2*em ;
    }
    void print(){
       string res = local_transport ? "local train " : "long distance train ";
       string w = one_way ? "one way " : "return ";
       cout<< w <<" "<<res; 
       Transport::print();
    }
    ~Train () {
        cout<<"    destructor Train: ";
        print();
    }
};
// 8..
class Cruise : public CO2Emission
{
private:
    float days, sea_days;
    float get_co2_day(bool sd){
        if (sd == true)
            return 280;
        else 
            return 190;
    }
public:
    Cruise(){
        cout<< "\ncruise holiday data input: "<<endl;
        cout<< "number of days of the whole cruise: ";
        cin>> days;
        cout<< "number of sea days: ";
        cin>> sea_days;
    }
    Cruise(float d, float sd) : days(d), sea_days(sd) {}
    float get_co2(){
        float num_har_days = days - sea_days;
        float ems = get_co2_day(true) * sea_days;
        float emh = get_co2_day(false) * num_har_days;
        return (ems + emh) ; 
    }
    void print(){
        cout<< "cruise holiday (without flights): "<<days <<" days duration with " <<sea_days <<" sea days (sea day ";
        cout<< fixed << setprecision(3) <<get_co2_day(true)<< " kg CO2 / pkm, harbor day "<<get_co2_day(false) <<" kg CO2 / pkm) ";
        cout<< fixed << setprecision(1) << get_co2() <<" kg CO2 "<<endl;
    }
    ~Cruise() {
        cout<<"  destructor Cruise: ";
        print();
    }
};
// add 2..
class Wind : public Power
{
private:
    float get_co2_kWh(){
        return 0.086;
    }
public:
    Wind() {}
    Wind(float w) : Power(w) {}
    void print(){
        cout<<"wind ";
        Power::print();
    }
    ~Wind() {
        cout<<"    destructor Wind:  ";
        print();
    }
};
// add 3..
class Coal : public Power
{
private:
    bool anthracite;
    float get_co2_kWh(){
        if (anthracite == true)
            return 0.798;
        else 
            return 1.150;
    }
public:
    Coal(){
        char s;
        cout<<"\ncoal power data input: " <<"\ntype of coal: " <<"\n(a) anthracite coal" <<"\n(l) lignite" <<"\nyour choice: ";
        cin>>s;
        if(s == 'a'){
            anthracite = true;
        }
        else anthracite = false;
    }
    Coal( float d, bool b = true) :  Power(d) , anthracite(b) {}
    void print(){
        string r = anthracite ? "anthracite coal " : "lignite ";
        cout<< r;
        Power::print();
    }
    ~Coal() {
        cout<<"   destructor Coal:  ";
        print();
    }
};
// 9..
class CO2Footprint 
{
private:
    string name;
    CO2Emission* emissions ;
public:
    CO2Footprint (string n) : name(n), emissions(NULL) { }
    string get_name(){
        return name;
    }
    void add(CO2Emission* insert){
        if(emissions == nullptr){
            emissions = insert;
        }
        else {
            insert->set_next(emissions);
            emissions = insert;
        }
    }
    float get_sum_co2(){
        float total;
        CO2Emission* temp;
        temp = emissions;
        while (temp != nullptr)
        {
            total += temp->get_co2();
            temp = temp->get_next();
        }
        return total;  
    }
    void print(){
        cout<<"CO2 FOODPRINT FOR: "<<name<<endl;
        CO2Emission* p;
        p = emissions;
        while (p != nullptr)
        {
            p->print();
            p = p->get_next();
        }
        float sum = get_sum_co2();
        cout<<"TOTAL CO2 EMISSIONS: "<<fixed << setprecision(1) <<sum <<" kg = "<< sum/1000 << " tons"<<endl;  
    }
    ~CO2Footprint (){
        cout<<"destructor for CO2Footprint for "<<name<<" started..."<<endl;
        CO2Emission* tmp;
        while (emissions != nullptr)
        {
            tmp = emissions;
            emissions = emissions->get_next();
            delete tmp;
        }
        cout<<"\ndestructor CO2Foodprint done";
    }
};
// 10...
int main(void) {
    Bus* b2 = new Bus(true, 2200);
    Car* c2 = new Car(7.5, 5500);
    Cruise* h2 = new Cruise(14, 3);
    Flight* f2 = new Flight(2669.9);
    Train* t2 = new Train(false, 628.8,false);
    Wind* w2 = new Wind(2000);
    Coal* k2 = new Coal(2000);
    string name;
    cout<<"CO2 footprint for? ";
    cin>>name;
    CO2Footprint f(name);
    f.add(b2);
    f.add(c2);
    f.add(h2);
    f.add(f2);
    f.add(t2);
    f.add(w2);
    f.add(k2);
    string choice;
    do
    {
        cout<<"\nCO2 footprint input for "<<name<<endl;
        cout<<"(e) end\n(b) bus transport\n(c) car transport\n(f) flight tranport\n(h) holiday cruise\n(t) train transport\n(s) power from wind\n(g) power from coal\n(p) print all"<<endl;
        cin>>choice;
        if (choice =="e" || choice =="E"){
            return 1;
        }
        else if (choice =="b" || choice =="B")
        {
            Bus* b = new Bus;
                f.add(b);
        }
        else if (choice =="c" || choice =="C")
        {
            Car* c = new Car;
                f.add(c);
        }
        else if (choice =="f" || choice =="F")
        {
            Flight* fli = new Flight;
                f.add(fli);
        }
        else if (choice =="h" || choice =="H")
        {
            Cruise* cru = new Cruise;
                f.add(cru);
        }
        else if(choice =="t" || choice =="T")
        {
           Train* t = new Train;
                f.add(t);
        }
        else if(choice =="s" || choice =="S")
        {
           Wind* win = new Wind;
                f.add(win);
        }
        else if(choice =="g" || choice =="G")
        {
           Coal* coa = new Coal;
                f.add(coa);
        }
        else if (choice =="p" || choice =="P")
        {
            f.print();
        }
        else
            cerr<<"please enter a valid choice..";
    } while (1);
    
    return 0;
}
