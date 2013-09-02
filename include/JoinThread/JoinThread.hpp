////////////////////////////////////////////////////////////
//
// TTL - Tea Tank Library
// Copyright (C) 2013 Kevin R. Stravers (macocio@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#ifndef JOINTHREAD_HPP_INCLUDED
#define JOINTHREAD_HPP_INCLUDED

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <thread>
#include <functional>


namespace ttl
{
    ////////////////////////////////////////////////////////////
    /// \brief Scoped thread that joins at scope exit
    ///
    ////////////////////////////////////////////////////////////
    class JoinThread : public std::thread
    {
    public:

        ////////////////////////////////////////////////////////////
        /// \brief Constructor delegator
        ///
        /// \see std::thread::thread(...)
        ///
        ////////////////////////////////////////////////////////////
        JoinThread();

        ////////////////////////////////////////////////////////////
        /// \brief Constructor delegator
        ///
        /// \see std::thread::thread(...)
        ///
        ////////////////////////////////////////////////////////////
        template <typename ...Args>
        JoinThread(Args &&...args):std::thread(std::forward<Args>(args)...){}

        ////////////////////////////////////////////////////////////
        /// \brief Destructor
        ///
        /// Joins the thread
        ///
        ////////////////////////////////////////////////////////////
        ~JoinThread();

    };

} // Namespace ttl

#endif // JOINTHREAD_HPP_INCLUDED


////////////////////////////////////////////////////////////
/// \class JoinThread
/// \ingroup Utilities
///
/// This class works exactly like std::thread since it
/// inherits therefrom and delegates all constructor
/// arguments to std::thread::thread(...)
///
/// \code
/// int &n = 0;
/// JoinThread thr
/// (
///     [](int &number)
///     {
///         number++;
///         std::this_thread::sleep_for(std::chrono::seconds(3));
///     },
///     std::ref(n)
/// );
/// \endcode
///
/// Don't worry about detaching the thread, a check is
/// performed during destruction to make sure the thread
/// is joinable.
///
/// \see std::thread
///
////////////////////////////////////////////////////////////