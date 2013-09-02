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

#ifndef IPS_HPP_INCLUDED
#define IPS_HPP_INCLUDED

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <chrono>
#include <thread>
#include <ostream>


namespace ttl
{
    ////////////////////////////////////////////////////////////
    /// \brief Iteration limiter.
    ///
    /// Class encapsulating an iterative loop to limit its iterations/frames per second.
    ////////////////////////////////////////////////////////////
    class Ips
    {
    private:

        typedef std::chrono::microseconds us;
        typedef std::chrono::milliseconds ms;
        typedef std::chrono::seconds s;
        typedef std::chrono::minutes m;
        typedef std::chrono::hours h;

        typedef std::chrono::high_resolution_clock hre;
        typedef std::chrono::time_point<hre> tphre;

    public:

        ////////////////////////////////////////////////////////////
        /// \brief Constructor
        ///
        /// Initializes Ips with an unlimited framerate
        ///
        ////////////////////////////////////////////////////////////
        Ips();

        ////////////////////////////////////////////////////////////
        /// \brief Constructor
        ///
        /// \param ips The amount of iterations per second that this object will allow
        ///
        ////////////////////////////////////////////////////////////
        Ips(const float ips);

        ////////////////////////////////////////////////////////////
        /// \brief Destructor
        ///
        ////////////////////////////////////////////////////////////
        ~Ips();

        ////////////////////////////////////////////////////////////
        /// \brief Iteration limiter
        ///
        /// A call to this function checks the time between this limit
        /// and the last limit. If the time is under a specified value,
        /// then this function will call sleep. The length of the sleep
        /// will be just so long so that the desired iterations per
        /// second will be achieved.
        ///
        ////////////////////////////////////////////////////////////
        void limit();

        ////////////////////////////////////////////////////////////
        /// \brief Get the internal iterations per second value
        ///
        /// Method that returns the set iterations per second value.
        ///
        /// \return the number of iterations per second
        ///
        ////////////////////////////////////////////////////////////
        float getIps() const;

        ////////////////////////////////////////////////////////////
        /// \brief Set the internal iterations per second value
        ///
        /// A limit is deduced from the passed value since
        /// the limit and ips are intertwined. A limit of 33 ms approximates
        /// an ips value of 30. Setting either the limit or the ips
        /// are two ways of specifying a limit.
        ///
        /// \param ips The amount of iterations per second that this object will allow
        /// \see setLimit(const us &limit);
        ///
        ////////////////////////////////////////////////////////////
        void setIps(const float ips);

        ////////////////////////////////////////////////////////////
        /// \brief Returns the limit
        ///
        /// The limit is the minimum amount of time needed between two
        /// limit() calls in order to not invoke a sleep.
        ///
        /// \return the limit
        ///
        ////////////////////////////////////////////////////////////
        us getMinIterationTime() const;

        ////////////////////////////////////////////////////////////
        /// \brief Sets a new limit, undoes setIps()
        ///
        /// The limit is the minimum amount of time needed between two
        /// limit() calls in order to not invoke a sleep.
        /// The limit and ips are intertwined. A limit of 33 ms approximates
        /// an ips value of 30. Setting either the limit or the ips
        /// are two ways of specifying a limit.
        ///
        /// \param limit the limit
        /// \see setIps(const float ips);
        ///
        ////////////////////////////////////////////////////////////
        void setMinIterationTime(const us &limit);

        ////////////////////////////////////////////////////////////
        /// \brief Returns the time between the last two limit calls
        ///
        /// The delay is the value of time used between two limit calls.
        /// This means that the value represents the running time of
        /// the loop surrounding the Ips object. This can be used to
        /// check how much time is used to run the loop.
        ///
        /// \return the delay in microseconds
        ///
        ////////////////////////////////////////////////////////////
        us getDelay() const;

        ////////////////////////////////////////////////////////////
        /// \brief Output stream
        ///
        /// \param lhs The stream object to stream into
        /// \param rhs The amount of iterations per second that this object will allow
        ///
        ////////////////////////////////////////////////////////////
        friend std::ostream &operator<<(std::ostream &lhs, Ips &rhs);

    private:

        us
            min_time, ///< The minimum amount of time per iteration requested
            delay; ///< The delay of last iteration
        tphre
            t1, ///< Clock time since iteration start
            t2; ///< Clock time at iteration end
    };

} // Namespace ttl

#endif // IPS_HPP_INCLUDED


////////////////////////////////////////////////////////////
/// \class Ips
/// \ingroup Utilities
///
/// The Ips (Iterations per second) class is a generic frame- or iteration
/// limiting class. The class minimalistic and simple to use:
///
/// \code
/// // Limit to 30 frames per second
/// Ips t(30);
///
/// for(int i = 0; i < 200; ++i)
/// {
///     std::cout << i << (i < 199 ? " - " : "") << (i < 199 ? "" : "\n") << std::flush;
///
///     // Limit the speed
///     t.limit();
/// }
///
/// // Output IT (Iteration Time) and RTPI (Requested Time Per Iteration)
/// std::cout << t;
/// \endcode
///
////////////////////////////////////////////////////////////