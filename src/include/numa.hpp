#ifndef QLIBS_NUMA
#define QLIBS_NUMA

#include "include/types.hpp" 

namespace qlibs {

    enum integrationMethod {
        INTEGRATION_RECTANGULAR,
        INTEGRATION_TRAPEZOIDAL,
        INTEGRATION_SIMPSON,
    };

    class state {
        private:
            real_t x[ 3 ] = { 0.0, 0.0, 0.0 };
            void inline update( const real_t &s )
            {
                x[ 2 ] = x[ 1 ];
                x[ 1 ] = s;
            }
            integrationMethod intMethod{ INTEGRATION_TRAPEZOIDAL };
        public:
            virtual ~state() {}
            state( const real_t x0 = 0.0,
                   const real_t sn_1 = 0.0,
                   const real_t sn_2 = 0.0 ) noexcept
            {
                init( x0, sn_1, sn_2 );
            }
            void init( const real_t x0 = 0.0,
                       const real_t sn_1 = 0.0,
                       const real_t sn_2 = 0.0 ) noexcept;
            real_t integrate( const real_t s,
                              const real_t dt ) noexcept;
            real_t derivative( const real_t s,
                               const real_t dt ) noexcept;
            inline void setIntegrationMethod( integrationMethod m ) noexcept
            {
                intMethod = m;
            }
            real_t operator()( void ) const  noexcept
            {
                return x[ 0 ];
            }

            real_t operator*( real_t rValue) const noexcept
            {
                return x[ 0 ]*rValue;
            }
            real_t operator+( real_t rValue) const noexcept
            {
                return x[ 0 ]+rValue;
            }
            friend real_t operator*( real_t rValue,
                                     const state& s ) noexcept;
            friend real_t operator+( real_t rValue,
                                     const state& s ) noexcept;
    };

    inline real_t operator*( real_t rValue,
                             const state& s ) noexcept
    {
        return rValue*s.x[ 0 ];
    }
    inline real_t operator+( real_t rValue,
                             const state& s ) noexcept
    {
        return rValue+s.x[ 0 ];
    }

}

#endif /*QLIBS_NUMA*/