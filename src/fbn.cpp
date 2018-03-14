# include "fbn.h"

int main(int argc, char *argv[]) {

    F<int> f;
    f.f<A,A11,A12,A13,A14>(0,1,2,3,4);
    for ( auto & a : m ) {
        std::cout << a.first << std::endl;
        a.second->execute();
    }

    //f1< A, <int, < std::tuple<int,double,std::string> >A11, std::tuple<int,double,std::string> >( 0, in );
    //for ( auto & a : m ) {
    //    std::cout << a.first << std::endl;
    //    a.second->execute();
    //}



    return 0;

}
