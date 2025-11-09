#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/*
The Observer Pattern defines a one-to-many
dependency between objects so that when one
object changes state, all of its dependents are
notified and updated automatically.

The only thing the subject knows about an observer is that it
implements a certain interface 

We can add new observers at any time.

We never need to modify the subject to add new types of observers.

We can reuse subjects or observers independently of each other.

Changes to either the subject or an observer will not affect the other. 
*/

class IObserver
{
    public:
        virtual void update(float temp, float humidity, float pressure) = 0;
        virtual ~IObserver() {}
};

class ISubject
{
    public:
    virtual void registerObserver(IObserver *observer) = 0;
    virtual void removeObserver(IObserver *observer) = 0;
    virtual void notifyObservers() = 0;
    virtual ~ISubject() {}
};

class Display : public IObserver 
{
    public:
        void update(float temperature, float humidity, float pressure)
        {
            std::cout << "Display: Temperature = " << temperature
                      << "°C, Humidity = " << humidity
                      << "%, Pressure = " << pressure << " hPa\n";
        }
   };

class WeatherStation: public ISubject
{
    private:
        float _temp;
        float _humidity;
        float _pressure;
        std::vector<IObserver *> _observers;
    public:
        void registerObserver(IObserver *observer) 
        {
            _observers.push_back(observer);
        }

        void removeObserver(IObserver *observer)
        {
            _observers.erase(std::remove(_observers.begin(), _observers.end(), observer), _observers.end());
        }

        void notifyObservers()
        {
            // loop through all obsevers
            for (IObserver* observer : _observers)
            {
                observer->update(_temp, _humidity, _pressure);
            }
        }

        void setMeasurements(float temperature, float humidity, float pressure)
        {
            _temp = temperature;
            _humidity = humidity;
            _pressure = pressure;
            notifyObservers();
        }

        float getTemperature() 
        {
            return _temp;
        }
           
            float getHumidity() 
            {
                return _humidity;
            }
           
            float getPressure() 
            {
                return _pressure;
            }
};

int main()
{
    WeatherStation station;
    Display display1;
    Display display2;

    station.registerObserver(&display1);
    station.registerObserver(&display2);

    station.setMeasurements(10.5, 20.0, 30.2);

    station.setMeasurements(0.8, 0.4, 0.5);

    return 0;
}