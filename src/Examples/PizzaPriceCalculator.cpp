class Topping {
public:
    virtual float getPrice() = 0;
};

class Onions : public Topping {
public:
    string name = "onion";
    float price = 10;
    // Onions(string name, float price) {
    //     this->name = name;
    //     this->price = price;
    // }
    
    float getPrice() override {
        return this->price;
    }
};

class Mushroom : public Topping {
public:
    string name = "mushroom";
    float price = 20;
    Mushroom(string name, float price) {
        this->name = name;
        this->price = price;
    }
    
    float getPrice() override {
        return this->price;
    }
};

enum PizzaSize {
    SMALL,
    MEDIUM,
    LARGE
};

class Size {
public:
    virtual float getPrice() = 0;
};

class Small : public Size {
public:
    PizzaSize size = PizzaSize::SMALL;
    float price = 7;
    
    // Small(PizzaSize size, float price) {
    //     this->size = size;
    //     this->price = price;
    // }
    
    float getPrice() override {
        return this->price;
    }
};

class Base {
public:
    virtual float getPrice() = 0;
};

class Thin : public Base {
public:
    string base = "thin";
    float price = 5;
    
//     Thin(string base, float price) {
//         this->base = base;
//         this->price = price;
//     }
    
    float getPrice() override {
        return this->price;
    }
};

class Pizza {
public:
    vector<Topping*>toppings = {};
    Size* size;
    Base* base;
    
    void setSize(Size* size) {
        this->size = size;
    }
    
    void setBase(Base* base) {
        this->base = base;
    }
    
    void addTopping(Topping* topping) {
        this->toppings.push_back(topping);
    }
    
    float getPrice() {
        int price = this->size->getPrice() + this->base->getPrice();
        for(auto& topping : this->toppings) {
            price += topping->getPrice();
        }
        return price;
    }
};

class PizzaBuilder {
private:
    Pizza* pizza = new Pizza();
public:
    PizzaBuilder* addTopping(Topping* topping) {
        this->pizza->addTopping(topping);
        return this;
    }
    
    PizzaBuilder* setBase(Base* base) {
        this->pizza->setBase(base);
        return this;
    }
    
    PizzaBuilder* setSize(Size* size) {
        this->pizza->setSize(size);
        return this;
    }
    
    Pizza* build() {
        return this->pizza;
    }    
};

int main() {
    PizzaBuilder* builder = new PizzaBuilder();
    
    Topping* onion = new Onions();
    Base* base = new Thin();
    Size* small = new Small();
    
    Pizza* pizza = builder->addTopping(onion)
        ->setBase(base)
        // ->setSize(size)
        ->build();
    
    pizza->getPrice();
                            
}
