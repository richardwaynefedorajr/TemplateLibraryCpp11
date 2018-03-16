# include "lib.h"

int main(int argc, char *argv[]) {

    // Show a rigid example of each creational design pattern with templates, but also show some interesting creational patterns which extend the generic ideology

    // Template can produce any combination of base and derived classes
   
    std::cout << "Abstract factory: " << std::endl;
    
    AbstractFactory<A,A1,A2> factory;
    std::unique_ptr<A> a1 = factory.get1();
    std::unique_ptr<A> a2 = factory.get2();
    a1->print();
    a2->print();
   
    std::cout << std::endl;

    // Variadic template function can populate std::map with arbitrary number of derived classes accepting std::tuples for ctor arguments
   
    std::cout << "Variadic template factory: " << std::endl;
   
    std::map< std::string,std::unique_ptr<V> > m;
    f< std::map<std::string,std::unique_ptr<V> >,V,V1,V1 >(m,std::tuple<std::string,int>("V1:1",1),std::tuple<std::string,int>("V1:2",2));

    std::cout << "V1:1 " << m["V1:1"]->i << std::endl;
    std::cout << "V1:2 " << m["V1:2"]->i << std::endl;
    std::cout << std::endl;

    // Singleton resource manager with interface using proxy and facade functionality
    // DEBUG -> why aren't A1 and A2 printing
   
    std::cout << "Interface: " << std::endl;
   
    Interface<A,A1,A2> i = Interface<A,A1,A2>();
    i.set();
    i.print();
    
    std::cout << std::endl;

    // Builder can create objects with different member types
    // True builder pattern would have derived builders to apply different values for given templated type
    std::cout << "Builder: " << std::endl;

    B<int,int> b1;
    B<std::string,std::string> b2;
    Builder< int,int, B<int,int> > builder1;
    Builder< std::string, std::string, B<std::string,std::string> > builder2;
    int i1 = 1, i2 = 4;
    std::string s1 = "Hello", s2 = "world";

    builder1.build(i1,i2,b1);
    builder2.build(s1,s2,b2);

    b1.execute();
    b2.execute();
    
    std::cout << std::endl;

    return 0;

}
