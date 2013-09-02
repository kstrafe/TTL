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

#ifndef FLARE_HPP_INCLUDED
#define FLARE_HPP_INCLUDED

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <mutex> // std::unique_lock, std::mutex
#include <condition_variable> // std::condition_variable


namespace ttl
{
    ////////////////////////////////////////////////////////////
    /// \brief Simple signalling between threads.
    ///
    /// Works like a mutex, except that it's thread-safe when
    /// it comes to ownership. It also prevents spurious
    /// wakeups.
    ///
    ////////////////////////////////////////////////////////////
    class Flare
    {
    public:

        ////////////////////////////////////////////////////////////
        /// \brief Flare's constructor.
        ///
        /// \param skip_on_first_wait will skip the first wait()
        /// if true. This value is normally false.
        ///
        ////////////////////////////////////////////////////////////
        Flare(bool skip_on_first_wait = false);

        ////////////////////////////////////////////////////////////
        /// \brief Flare's destructor.
        ///
        /// Takes care of removing the object of this class.
        ///
        ////////////////////////////////////////////////////////////
        ~Flare();

        ////////////////////////////////////////////////////////////
        /// \brief Alias of notify_one()
        ///
        /// \see notify_one()
        ///
        ////////////////////////////////////////////////////////////
        void notify();

        ////////////////////////////////////////////////////////////
        /// \brief Notifies a single thread.
        ///
        /// One thread waiting on this object will be freed,
        /// and if the thread was not waiting, it will skip
        /// wait when it iterates over it.
        ///
        ////////////////////////////////////////////////////////////
        void notify_one();

        ////////////////////////////////////////////////////////////
        /// \brief Notifies all threads in wait.
        ///
        /// Any thread waiting on this object will be freed,
        /// and if the threads were not waiting, it will skip
        /// wait when it iterates over it.
        ///
        ////////////////////////////////////////////////////////////
        void notify_all();


        ////////////////////////////////////////////////////////////
        /// \brief Wait until the next notification.
        ///
        /// If a notification was sent whilst not being
        /// inside wait, then wait will simply be skipped.
        ///
        ////////////////////////////////////////////////////////////
        void wait();

    private:

        std::mutex m_mx; ///< Used in the unique_lock
        std::condition_variable m_cndvar; ///< The actual condition variable
        bool m_notifications : 1; ///< Anti-spurious wakeup boolean and waiting state
    };

} // Namespace ttl

#endif // FLARE_HPP_INCLUDED


////////////////////////////////////////////////////////////
/// \class Flare
/// \ingroup Programming Utilities
///
/// With the use of flares, signalling between threads becomes an easy
/// and safe task to perform. The use of condition variables creates
/// an environment in which flares perform very well. The class
/// uses mutexes and locks internally so there is no need for the
/// programmer to be vigilant of writing thread-friendly code.
///
///
/// \code
/// // A simple producer/consumer using flares
///
/// // Declare flare objects
/// Flare consume, produce;
///
/// // Declare a queue used to communicate our producer/consumer data
/// std::queue<int> conveyor;
///
/// // We use a sum to check if no errors occured
/// int sum = 0;
///
/// // A thread that consumes
/// std::thread consumer
/// (
///     [&]()
///     {
///         for (int consumed = 0; consumed < 100000; ++consumed)
///         {
///             consume.wait(); // Waits until there is a produced value available
///
///             sum += conveyor.front();
///             conveyor.pop();
///
///             produce.notify(); // Notifies the producer that the consumer has consumed the variable
///         }
///     }
/// );
///
/// // Main thread produces
/// for (int produced = 0; produced < 100000; ++produced)
/// {
///     conveyor.push(1);
///
///     consume.notify(); // Notifies the consumer that a single number is available
///     produce.wait(); // Waits until the consumer has removed the number from the queue
/// }
///
/// consumer.join();
///
/// // This should output a value of 100000
/// std::cout << sum << std::endl;
///
/// \endcode
///
////////////////////////////////////////////////////////////
