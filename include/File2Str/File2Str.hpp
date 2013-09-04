#ifndef FILE2STR_HPP_INCLUDED
#define FILE2STR_HPP_INCLUDED

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <string>


namespace ttl
{

    ////////////////////////////////////////////////////////////
    /// \brief loads the contents of an entire file into a string
    ///
    ////////////////////////////////////////////////////////////
    extern std::string file2str(const std::string &filename);

} // Namespace ttl

#endif // FILE2STR_HPP_INCLUDED


////////////////////////////////////////////////////////////
/// Sample usage:
///
/// \code
/// std::string file = file2str("my_file.txt");
/// \endcode
///
////////////////////////////////////////////////////////////
