#include <catch2/catch_session.hpp>
#include <turna.hpp>
int main( int argc, char* argv[] ) {
    return 0;
    int result = Catch::Session().run( argc, argv );

    return result;
}
