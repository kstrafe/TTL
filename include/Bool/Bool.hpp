#ifndef BOOL_HPP_INCLUDED
#define BOOL_HPP_INCLUDED

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////


namespace ttl
{

    ////////////////////////////////////////////////////////////
    /// \brief Simple boolean with methods
    ///
    ////////////////////////////////////////////////////////////
    class Bool
    {
    public:

        ////////////////////////////////////////////////////////////
        /// \brief Constructor
        ///
        /// Does not initialize the boolean
        ///
        ////////////////////////////////////////////////////////////
        Bool();

        ////////////////////////////////////////////////////////////
        /// \brief Constructor
        ///
        /// Initializes the boolean
        ///
        ////////////////////////////////////////////////////////////
        Bool(const bool arg);

        ////////////////////////////////////////////////////////////
        /// \brief Sets the boolean to a value
        ///
        /// \param state The state that it will be set to
        ///
        ////////////////////////////////////////////////////////////
        void reset(bool state = true);

        ////////////////////////////////////////////////////////////
        /// \brief Fetches the bool, then sets it to true
        ///
        /// \return the bool from before the set to true
        ///
        ////////////////////////////////////////////////////////////
        bool fetch_and_enable();

        ////////////////////////////////////////////////////////////
        /// \brief Fetches the bool, then sets it to false
        ///
        /// \return the bool from before the set to false
        ///
        ////////////////////////////////////////////////////////////
        bool fetch_and_disable();

        ////////////////////////////////////////////////////////////
        /// \brief Fetches the bool, then flips the state
        ///
        /// \return the bool from before it was flipped
        ///
        ////////////////////////////////////////////////////////////
        bool fetch_and_flip();

        ////////////////////////////////////////////////////////////
        /// \brief Fetches the bool, then sets it to a state
        ///
        /// \param state The state the bool wil be set to
        /// \return the bool from before the set to state
        ///
        ////////////////////////////////////////////////////////////
        bool fetch_and_set(bool state);

        ////////////////////////////////////////////////////////////
        /// \brief Fetches the bool
        ///
        /// \return The raw bool
        ///
        ////////////////////////////////////////////////////////////
        operator bool();

        ////////////////////////////////////////////////////////////
        /// \brief Fetches the bool, then sets it to a state
        ///
        /// \param state The state the bool wil be set to
        /// \return the bool from before the set to state
        ///
        ////////////////////////////////////////////////////////////
        template <typename T>
        Bool &operator=(T &&a)
        {
            m_b = a;
            return *this;
        }

    private:

        bool m_b : 1;

    };

} // Namespace ttl

#endif // BOOL_HPP_INCLUDED
