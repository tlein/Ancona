#ifndef Ancona_Util_Algorithm_ContainerExtensions_H_
#define Ancona_Util_Algorithm_ContainerExtensions_H_

#include <algorithm>
#include <iterator>
#include <sstream>
#include <utility>

namespace alg
{

template <class Container, class T>
bool contains(Container & c, T & v)
{
    return std::find(c.begin(), c.end(), v) != c.end();
}

template <class Container, class T>
void erase(Container & c, T & v)
{
    c.erase(std::remove(c.begin(), c.end(), v), c.end());
}

template <typename T>
std::string to_string(T value)
{
    std::ostringstream os;
    os << value;
    return os.str();
}

template <typename R, typename Container, typename Transform>
auto map(
        const Container & c,
        const Transform & t
    )
{
    std::vector<R> returnContainer(c.size());
    alg::for_each(c, [](auto element){
        returnContainer.push(t(element))
    });
    return returnContainer;
}

}

#endif
