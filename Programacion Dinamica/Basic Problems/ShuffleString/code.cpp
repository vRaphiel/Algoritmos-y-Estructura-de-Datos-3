#include <iostream>
#include <vector>
 
class Shuffle {
public: 
    Shuffle(const std::string& a, const std::string& b, const std::string& c);
    void is_shuffle ( const unsigned int i, const unsigned int j );
    void init ();
    void printXYZ () const;
    void printDPmat () const;
    bool get ( const unsigned int i, const unsigned int j ) const;
 
private:
    const std::string x;
    const std::string y;
    const std::string z;
    const std::string::size_type n, m;
    std::vector<std::vector<bool>> DPmat;
};
 
Shuffle::Shuffle(const std::string& a, const std::string& b, const std::string& c) : x{a}, y{b}, z{c}, n{x.size()}, m{y.size()} {
    DPmat.resize(n+1);
    for ( unsigned int i = 0 ; i <= n; i++ )
        DPmat[i].resize(m+1);
}
 
void Shuffle::printXYZ () const {
    std::cout << x << std::endl << y << std::endl << z << std::endl;
}
 
void Shuffle::printDPmat () const {
    for ( unsigned int i = 0; i <= n; ++i ) {
        for ( unsigned int j = 0; j <= m; ++j ) 
            std::cout << DPmat[i][j] << " ";
        std::cout << std::endl;
    }
}
 
void Shuffle::is_shuffle ( const unsigned int i, const unsigned int j ) {
    DPmat[i][j] = ((x[i-1] == z[i+j-1]) && DPmat[i-1][j]) || ((y[j-1] == z[i+j-1]) && DPmat[i][j-1] );
//-SMS     printf ( "x[%i]: %c y[%i]: %c z[%i]: %c\n", i-1, x[i-1], j-1, y[j-1], i+j-1, z[i+j-1] );
//-SMS     printDPmat();
}
 
bool Shuffle::get ( const unsigned int i, const unsigned int j ) const {
    return DPmat[i][j];
}
 
void Shuffle::init () {
    DPmat[0][0] = true;
 
    for ( std::string::size_type i = 0; i <= n; ++i )
    for ( std::string::size_type j = 0; j <= m; ++j )
        DPmat[i][j] = false;
 
    DPmat[0][0] = true;
 
    for ( std::string::size_type i = 1; i <= n; ++i )
        if ( !x.compare(0,i,z,0,i) )
            DPmat[i][0] = true;
             
    for ( std::string::size_type j = 1; j <= m; ++j )
        if ( !y.compare(0,j,z,0,j) )
            DPmat[0][j] = true;
}
 
int main () {
    const std::string X {"chocolate"};
    const std::string Y {"chips"};
    const std::string Z {"cchocohilaptes"};
//-SMS     const std::string Z {"chocochilatspe"};
    Shuffle shuffle(X, Y, Z);
    shuffle.printXYZ();
 
    shuffle.init();
 
    for ( unsigned int i = 1; i <= X.size(); ++i ) {
        for ( unsigned int j = 1; j <= Y.size(); ++j ) {
            if ( !shuffle.get(i-1,j) && !shuffle.get(i,j-1) )
                continue;
            shuffle.is_shuffle ( i, j );
        }
    }
 
    shuffle.printDPmat();
 
    if ( shuffle.get (X.size(), Y.size() ) )
        std::cout << Z << " is a shuffle of " << X << " and " << Y << std::endl;
    else
        std::cout << Z << " is NOT a shuffle of " << X << " and " << Y << std::endl;
    return 0;
}