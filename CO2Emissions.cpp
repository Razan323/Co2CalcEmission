#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;
// 1..
class Bus
{
private:
    bool local_transport;
    float km;
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
        float k;
        cout<<"\nbus travel data input:"<<endl;
        cout<<"(1) local transport"<<"\n"<<"(2) long distance"<<endl;
        cout<<"your choice: ";
        cin>>c;
        cout<<"kilometers: ";
        cin>>k;
        if( c == 1)
            local_transport = true;
        else local_transport = false;
        km = k;
    }
    Bus(bool l, float k) : local_transport(l) , km(k) {};
    float get_co2(){
        float co2_pkm = get_co2_pkm();
        return co2_pkm * km;
    }
    void print(){
        string res = local_transport ? "local transport: " : "long distance: ";
        cout<< "Bus travel " << res << fixed <<
        setprecision(1) << km <<" km ";
        cout<<"( "<<fixed << setprecision(3) << get_co2_pkm() << " kg CO2 / pkm) "<< fixed<< setprecision(1) << get_co2() << " kg CO2"<<endl;
    }
    ~Bus(){}
};
// 2..
class Car 
{
private: 
    float l_fuel_km , km;
    float get_co2_km (){
        float em_per_100km = 2.3;
        float em_per_1km = (em_per_100km/100) * l_fuel_km;
        return em_per_1km;
    }
public: 
    Car(){
        cout<< "\npassenger car travel data input: "<<endl;
        cout<< "Consumption liter of petrol per 100 kilometers: ";
        cin>> l_fuel_km;
        cout<< "kilometers: ";
        cin>> km;
    }
    Car(float f, float k) : l_fuel_km(f) , km(k) {}
    float get_co2(){
        float em = get_co2_km();
        return em * km;
    }
    void print(){
        cout<< "passenger car travel: "<< fixed << setprecision(1) << km <<" km ";
        cout<< "( "<< fixed << setprecision(3) << get_co2_km() <<" kg CO2 / km) ";
        cout<< fixed << setprecision(1) << get_co2() << " kg CO2" <<endl;
    }
    ~Car() { }
};
// 3..
class Cruise
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
    ~Cruise() {}
};
// 4..
class Flight 
{
private:
    float km;
    float get_co2_pkm() {
        return 0.27 ;
    }
public:
    Flight() {
        cout<< "\nflight travel data input: "<<endl;
        cout<< "kilometers: ";
        cin>> km;
    }
    Flight(float k) : km(k) {}
    float get_co2() {
        return km * get_co2_pkm();
    }
    void print() {
        cout<< "flight travel: " <<fixed << setprecision(1) << km << " km ";
        cout<< "( " << fixed<< setprecision(3) << get_co2_pkm() << " kg CO2 / pkm) ";
        cout<< fixed << setprecision(1) << get_co2() << " kg CO2 "<<endl;
    }
    ~Flight () {}
};
// 5..
class Train 
{
private:
    bool local_transport, one_way ;
    float km ;
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
        cout<<"\ntrain travel data input:"<<endl;
        cout<<"(1) local transport"<<'\n'<<"(2) long distance"<<endl;
        cout<<"your choice: ";
        cin>>c;
        cout<<"kilometers: ";
        cin>>km;
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
    Train(bool t, float k, bool w = true) : local_transport(t), km(k), one_way(w) {}
    float get_co2(){
        float em = get_co2_pkm();
        if(one_way == true)
            return em * km;
        
        else 
            return (2*em*km) ;
    }
    void print(){
       string res = local_transport ? "local transport: " : "long distance: ";
       string w = one_way ? "one way, " : "return, ";
       cout<< "train travel " << res <<fixed<< setprecision(1) << km <<" km (";
       cout<< w <<fixed<< setprecision(3) << get_co2_pkm() << " kg CO2 / pkm) ";
       cout<< fixed <<setprecision(1) << get_co2() << " kg CO2"<<endl;
    }
    ~Train () {}
};
// 6..
int main(void){
    Bus b1;
    Bus* b2 = new Bus(true, 2200);
    b1.print();
    b2->print();
    Car c1;
    Car* c2 = new Car(7.5, 5500);
    c1.print();
    c2->print();
    Cruise h1;
    Cruise* h2 = new Cruise(14, 3);
    h1.print();
    h2->print();
    Flight f1;
    Flight* f2 = new Flight(2669.9);
    f1.print();
    f2->print();
    Train t1;
    Train* t2 = new Train(false, 628.8,false);
    t1.print();
    t2->print();
    float total = b1.get_co2() + b2->get_co2() + c1.get_co2() + c2->get_co2() + h1.get_co2() + h2->get_co2() + f1.get_co2() + f2->get_co2() + t1.get_co2() + t2->get_co2();
  
    cout<< "\nthe added total of all CO2 emissions is "<<total <<" kg = "<<setprecision(1) <<total/1000 << " tons"<<endl;
    cout<< "\nBased purely on the CO2 absorption capacity of nature, each world citizen should currently afford a maximum of around 2.3 tons per year." <<endl;

    delete b2;
    delete c2;
    delete h2;
    delete f2;
    delete t2;
    return 0;
}