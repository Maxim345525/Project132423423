#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Rocket; 
class System {
public:
    virtual void receiveMessage(const string& message) const = 0;
    virtual void sendMessage(const string& message) const = 0;
    virtual void setMediator(Rocket* mediator) = 0;
};
class Rocket {
public:
    void registerSystem(System* system) {
        systems.push_back(system);
        system->setMediator(this);
    }
    void launch() const {
        cout << "Початок запуску ракети..." << endl;
        for (const auto& system : systems) {
            system->sendMessage("Запуск ракети!");
        }
    }
    void sendMessage(const string& message, const System* sender) const {
        for (const auto& system : systems) {
            if (system != sender) {
                system->receiveMessage(message);
            }
        }
    }
private:
    vector<System*> systems;
};
class EngineControlSystem : public System {
public:
    void receiveMessage(const std::string& message) const override {
        cout << "Система контролю двигуна отримала повідомлення: " << message << endl;
    }
    void sendMessage(const string& message) const override {
        mediator->sendMessage(message, this);
    }
    void setMediator(Rocket* mediator) override {
        this->mediator = mediator;
    }
private:
    Rocket* mediator;
};
class NavigationSystem : public System {
public:
    void receiveMessage(const string& message) const override {
        cout << "Система навігації отримала повідомлення: " << message << endl;
    }
    void sendMessage(const string& message) const override {
        mediator->sendMessage(message, this);
    }
    void setMediator(Rocket* mediator) override {
        this->mediator = mediator;
    }
private:
    Rocket* mediator;
};
int main() {
    Rocket rocket;
    EngineControlSystem engineControlSystem;
    NavigationSystem navigationSystem;
    rocket.registerSystem(&engineControlSystem);
    rocket.registerSystem(&navigationSystem);
    rocket.launch();
    return 0;
}