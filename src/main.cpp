# include "lib.h"

int main(int argc, char *argv[]) {

    // Show a rigid example of each creational design pattern with templates, but also show some interesting creational patterns which extend the generic ideology

    // Template can produce any combination of base and derived classes
    AbstractFactory<A,A1,A2> factory;
    std::unique_ptr<A> a1 = factory.get1();
    std::unique_ptr<A> a2 = factory.get2();
    a1->get();
    a2->get();

    // Variadic template function can populate std::map with arbitrary number of derived classes accepting std::tuples for ctor arguments
    std::map< std::string,std::unique_ptr<Avar> > m;
    f< std::map<std::string,std::unique_ptr<Avar> >,Avar,A1var,A1var >(m,std::tuple<std::string,int>("Avar1:1",1),std::tuple<std::string,int>("Avar1:2",2));

    std::cout << "Avar1:1 " << m["Avar1:1"]->i << std::endl;
    std::cout << "Avar1:2 " << m["Avar1:2"]->i << std::endl;


    // Builder can create objects with different member types
    // True builder pattern would have derived builders to apply different values for given templated type
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

    // Singleton resource manager with interface using proxy and facade functionality
    // DEBUG -> why aren't A1 and A2 printing
    Interface<A,A1,A2> i = Interface<A,A1,A2>();
    i.set();
    i.get();

    return 0;

}
