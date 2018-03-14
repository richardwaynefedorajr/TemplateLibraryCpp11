# include <iostream>
# include <memory>
# include <utility>
# include <map>
# include <vector>
# include <tuple>

// Generic classes for testing
class A { public: virtual void get() = 0; };
class A1 : public A { public: void get() { std::cout << "A1" << std::endl; } };
class A2 : public A { public: void get() { std::cout << "A2" << std::endl; } };

// Variadic abstract factory function (pass ctor arguments as tuple)
class Avar { public: int i; };
class A1var : public Avar { public: A1var(std::tuple<std::string,int> t) { i = std::get<1>(t); } };

template<typename M, typename B, typename D, typename T> void f(M & m, T t) {
        m[std::get<0>(t)] = std::unique_ptr<B>( new D(t) );
}
template<typename M, typename B, typename D1, typename D2, typename ...Ds, typename T, typename ... Ts> void f(M & m, T t, Ts ... Args) {
        m[std::get<0>(t)] = std::unique_ptr<B>( new D1(t) );
            f<M,B,D2,Ds...>(m,Args...);
}

// Abstract Factory
template <typename B, typename D1, typename D2> class AbstractFactory {
    public:
        template <typename... X>
        std::unique_ptr<B> get1(X... args) { return std::move( std::unique_ptr<B>( new D1(args...) ) ); }
        template <typename... X>
        std::unique_ptr<B> get2(X... args) { return std::move( std::unique_ptr<B>( new D2(args...) ) ); }
};

// Builder
template<typename T1, typename T2> class B {
    public:
        void execute() { std::cout << "m_T1: " << m_T1 << " m_T2: " << m_T2 << std::endl; }
        void setT1(T1 t1) { m_T1 = t1; }
        void setT2(T2 t2) { m_T2 = t2; }
        T1 m_T1;
        T2 m_T2;
};

template<typename T1, typename T2, typename C> class Builder {
    public:
        void build(T1 t1, T2 t2, C & c) { c.setT1(t1); c.setT2(t2); } 
        T1 m_T1;
        T2 m_T2;
};

// General resource management interface (Singleton, interface, proxy, facade elements)
template<typename T, typename T1, typename T2> class Interface;
template<typename T, typename T1, typename T2> class Singleton {
   
    friend class Interface<T,T1,T2>;
    
    public:
        ~Singleton() = default;
    private:
        Singleton() { };
        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;
        Singleton(Singleton&&) = delete;
        Singleton& operator=(Singleton&&) = delete;

        static std::unique_ptr<Singleton> m_instance;
        
        static Singleton& get() { 
            if ( !m_instance ) { m_instance.reset(new Singleton); }
            return *m_instance.get();
        }

        void create() { m_T1 = m_factory.get1(); m_T2 = m_factory.get2(); }
        
        AbstractFactory<T,T1,T2> m_factory;
        std::unique_ptr<T> m_T1;
        std::unique_ptr<T> m_T2;

};

template<typename T, typename T1, typename T2>
std::unique_ptr< Singleton<T,T1,T2> > Singleton<T,T1,T2>::m_instance = nullptr;

// Declaration of interface class with attributes of proxy and facade design patterns
template<typename T, typename T1, typename T2> class Interface {
    public:
        Interface() { m_Singleton = &Singleton<T,T1,T2>::get(); }
        void set() { m_Singleton->create(); }
        void get() { m_Singleton->m_T1.get(); m_Singleton->m_T2.get(); }
    private:
        Singleton<T,T1,T2>* m_Singleton;
};
