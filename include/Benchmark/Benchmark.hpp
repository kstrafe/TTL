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

#ifndef BENCHMARK_HPP_INCLUDED
#define BENCHMARK_HPP_INCLUDED

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <utility>
#include <chrono>
#include <ostream>
#include <functional>


namespace ttl
{

    ////////////////////////////////////////////////////////////
    /// \brief A benchmarking class
    ///
    /// A class designed for handling benchmarks of functions.
    /// It is possible to use member functions, lambdas,
    /// function pointers and const function pointers (normal
    /// functions).
    ///
    ////////////////////////////////////////////////////////////
    class Benchmark
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
        /// \param title The title to give this benchmark
        /// \param iterations The amount of calls to benchmark
        ///
        ////////////////////////////////////////////////////////////
        Benchmark(const char *title = "Unnamed benchmark", const std::size_t iterations = 1);

        ////////////////////////////////////////////////////////////
        /// \brief Constructor
        ///
        /// \param title The title to give this benchmark
        /// \param iterations The amount of calls to benchmark
        ///
        ////////////////////////////////////////////////////////////
        explicit Benchmark(const std::string &title, const std::size_t iterations = 1);

        ////////////////////////////////////////////////////////////
        /// \brief Constructor
        ///
        /// \param iterations The amount of calls to benchmark
        ///
        ////////////////////////////////////////////////////////////
        Benchmark(const std::size_t iterations = 1);

        ////////////////////////////////////////////////////////////
        /// \brief Copy constructor
        ///
        /// \param benchmark The benchmark to copy
        ///
        ////////////////////////////////////////////////////////////
        Benchmark(const Benchmark &benchmark);

        ////////////////////////////////////////////////////////////
        /// \brief Move constructor
        ///
        /// \param benchmark The benchmark to move
        ///
        ////////////////////////////////////////////////////////////
        Benchmark(Benchmark &&benchmark);

        ////////////////////////////////////////////////////////////
        /// \brief Copy assignment
        ///
        /// \param benchmark The benchmark to move
        /// \return A reference to itself
        ///
        ////////////////////////////////////////////////////////////
        Benchmark &operator=(const Benchmark &benchmark);

        ////////////////////////////////////////////////////////////
        /// \brief Move assignment
        ///
        /// \param benchmark The benchmark to move
        /// \return A reference to itself
        ///
        ////////////////////////////////////////////////////////////
        Benchmark &operator=(Benchmark &&benchmark);

        ////////////////////////////////////////////////////////////
        /// \brief Destructor
        ///
        ////////////////////////////////////////////////////////////
        ~Benchmark();

        ////////////////////////////////////////////////////////////
        /// \brief Actual running algorithm
        ///
        /// Will loop over the function n times specified by
        /// setIterations or by the constructor. The running time
        /// will be added to the old running time and then halfed
        /// in order to approximate an average.
        ///
        /// \param args first a function and then optional arguments
        ///
        ////////////////////////////////////////////////////////////
        template </*typem_name Fun, */typename ...Args>
        void run(/*Fun &&fnc, */Args &&...args)
        {
            tphre before, after;
            auto fnc = std::bind(/*fnc, */std::forward<Args>(args)...);
            before = hre::now();

            for (std::size_t i = 0; i < m_iterations; ++i)
    //            fnc(std::forward<Args>(args)...); // Does not work with methods
                fnc(); // Works with methods
            after = hre::now();
            m_average = (m_average + std::chrono::duration_cast<us>(after - before).count()) / static_cast<float>(m_iterations);
        }

        ////////////////////////////////////////////////////////////
        /// \brief Reset the average running time
        ///
        ////////////////////////////////////////////////////////////
        void resetAverageRunTime();

        ////////////////////////////////////////////////////////////
        /// \brief Set the amount of iterations per benchmark
        ///
        ////////////////////////////////////////////////////////////
        void setIterations(const std::size_t amount);

        ////////////////////////////////////////////////////////////
        /// \brief Get the average running time per benchmark
        ///
        /// \return the running time in microseconds
        ///
        ////////////////////////////////////////////////////////////
        float getAverageRunTime() const;

        ////////////////////////////////////////////////////////////
        /// \brief Overload of the ostream operator
        ///
        /// Outputs the name of the benchmark and the time
        /// cost per iteration.
        ///
        /// \param lhs the stream
        /// \param rhs the benchmark object
        /// \return A reference to the std::ostream object
        ///
        ////////////////////////////////////////////////////////////
        friend std::ostream &operator<<(std::ostream &lhs, const Benchmark &rhs);

    private:

        std::size_t m_iterations; ///< Iterations per run
        float m_average; ///< Average running time per call
        std::string m_name; ///< Title of this benchmark
    };

} // Namespace ttl

#endif // BENCHMARK_HPP_INCLUDED


////////////////////////////////////////////////////////////
/// \class Benchmark
/// \ingroup Programming Utilities
///
/// Benchmark is used to easily set up a benchmarking
/// environment for any function. The class has a high
/// amount of dynamicity and allows for virtually any
/// function to be called, even virtual functions.
///
///
/// \code
/// // Declare a new benchmarking unit
/// Benchmark ben("If statement", 10000);
///
/// // Run the benchmark
/// ben.run
/// (
///     // Use this lambda function
///     [](int value)
///     {
///         if (value % 2)
///             value = 0;
///     },
///     0 // With this as argument
/// );
///
/// // Output the results to the std::cout std::ostream
/// std::cout << ben << std::endl;
/// \endcode
///
/// For virtual functions and non-lambda functions;
/// the syntax that goes into run is forwarded into
/// std::bind(...), so the argument order is the same.
///
/// \code
/// // Declare and define a base and derived class
/// class Base{public: virtual void fnc(volatile int &num){} virtual ~Base(){}};
/// class Derived : public Base{public:virtual void fnc(volatile int &num) override{num++;}};
///
/// // Declare a number volatile to avoid compiler optimizations
/// volatile int number = 0;
///
/// // Create an object of the class
/// Base *bptr = new Derived;
///
/// // Declare a benchmarking object, 100k iterations
/// Benchmark virtual_call("Virtual method call", 10000000);
///
/// // Run the benchmark
/// virtual_call.run
/// (
///     &Base::fnc, // use this function
///     bptr, // and this object pointer (this)
///     std::ref(number) // with this argument, must explicitly use std::ref
/// );
///
/// // Delete the pointer
/// delete bptr;
///
/// // Output the data to our console window
/// std::cout << virtual_call;
///
/// // Now we know for sure if the virtual function was delegated or not:
/// std::cout << "number: " << number << std::endl;
/// \endcode
///
////////////////////////////////////////////////////////////