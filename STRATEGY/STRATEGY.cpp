#include <iostream>
using namespace std;

/*
The Strategy Pattern defines a family of algorithms,
encapsulates each one, and makes them interchangeable.
Strategy lets the algorithm vary independently from
clients that use it.
*/

// algorithm interface
class IFlyBehavior
{
    public:
    virtual void fly() = 0;

};

// algorithm 1
class FlyWithWings: public IFlyBehavior
{
    public:
    void fly()
    {
        cout << "fly with wings\n";
    }
};

// algorithm 2
class NoFlyBehavior: public IFlyBehavior
{
    public:
    void fly()
    {
        cout << "cannot fly\n";
    }
};

class Duck
{
    private:
    IFlyBehavior* _flybehavior;

    public:
        void swim()
        {
            cout << "swim\n";
        }
        void display()
        {
            cout << "display\n";
        }

        void setFlyBehavior(IFlyBehavior* flybehavior)
        {
            _flybehavior = flybehavior;
        }

        void performFly()
        {
            _flybehavior->fly();
        }

};

class RubberDuck: public Duck
{
    public:
    RubberDuck()
    {
        NoFlyBehavior noflybehavior;
        this->setFlyBehavior((IFlyBehavior *)&noflybehavior);
    }
    void display()
    {
        cout << "display RubberDuck" << endl;
    }

};

int main()
{
    IFlyBehavior *fbehavior = new NoFlyBehavior();

    // create object
    RubberDuck rduck = RubberDuck();
    rduck.display();
    rduck.performFly();

    // change the algo runtime
    FlyWithWings flywithwingsobj;
    rduck.setFlyBehavior((IFlyBehavior *)&flywithwingsobj);
    rduck.performFly();
    
    return 0;
}