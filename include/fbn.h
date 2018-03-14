# include <iostream>
# include <memory>
# include <utility>
# include <map>
# include <vector>
# include <tuple>

class A {
    public:
        A(int in) : i(in) {  }
    	virtual void execute() = 0;
        int i;
};

class A1 : public A { 
    public:
        A1(int in) : A(in) {  }
	    virtual void execute() {  }
};

class A11 : public A1 { 
    public:
        A11(int in) : A1(in) {  }
	    virtual void execute() { std::cout << "A11: " << i << std::endl; }
};

class A12 : public A1 { 
    public:
        A12(int in) : A1(in) {  }
	    virtual void execute() { std::cout << "A12: " << i << std::endl; }
};

class A13 : public A1 { 
    public:
        A13(int in) : A1(in) {  }
	    virtual void execute() { std::cout << "A13: " << i << std::endl; }
};

class A14 : public A1 { 
    public:
        A14(int in) : A1(in) {  }
	    virtual void execute() { std::cout << "A14: " << i << std::endl; }
};

std::vector<std::string> names = {"A11","A12","A13","A14"};
std::map<std::string,std::unique_ptr<A> > m;

//template<typename C1, typename C2> void f(int N) {
//    m[names.at(N)] = std::unique_ptr<C1>( new C2() );
//}
//template<typename C1, typename C2, typename C3, typename ... X> void f(int N) {
//    m[names.at(N)] = std::unique_ptr<C1>( new C2() );
//    f<C1,C3,X ...>(++N);
//}

template<typename ... I> class F {
    public:
        template<typename C1, typename C2> void f(int N, I i)  { m[names.at(N)] = std::unique_ptr<C1>( new C2(i) ); }
        template<typename C1, typename C2, typename C3, typename ... X> void f(int N, I i, I ... args ) {
            m[names.at(N)] = std::unique_ptr<C1>( new C2(i) );
            f<C1,C3,X ...>(++N, args ...); 
        }
        template<typename ... C> void f(int N, I ... args) { f<C...>(N,args); }
};

//template<typename B, typename D, typename ... Args > void f1(int N, Args ... args) { m[names.at(N)] = std::unique_ptr<B>( new D(args...) ); }


