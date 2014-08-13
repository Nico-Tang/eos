/* vim: set sw=4 sts=4 et foldmethod=syntax : */

/*
 * Copyright (c) 2010 Danny van Dyk
 *
 * This file is part of the EOS project. EOS is free software;
 * you can redistribute it and/or modify it under the terms of the GNU General
 * Public License version 2, as published by the Free Software Foundation.
 *
 * EOS is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef EOS_GUARD_SRC_UTILS_INTEGRATE_HH
#define EOS_GUARD_SRC_UTILS_INTEGRATE_HH 1

#include <eos/utils/complex.hh>
#include <eos/utils/exception.hh>

#include <array>
#include <functional>

namespace eos
{
    /// @{
    /*!
     * Numerically integrate functions of one real-valued parameter.
     *
     * Uses the Delta^2-Rule by Aitkin to refine the result.
     *
     * @param f      Integrand.
     * @param a      Lower limit of the domain of integration.
     * @param b      Upper limit of the domain of integration.
     * @param n      Number of evaluations, must be a power of 2 and no less than 16.
     *               If omitted, use default value. Can be set/retrieved by
     *               set_n()/get_n().
     */
    double integrate(const std::function<double (const double &)> & f, const double & a, const double & b);
    double integrate(const std::function<double (const double &)> & f, const double & a, const double & b, unsigned n);

    complex<double> integrate(const std::function<complex<double> (const double &)> & f, const double & a, const double & b);
    complex<double> integrate(const std::function<complex<double> (const double &)> & f, const double & a, const double & b, unsigned n);

    template <std::size_t k> std::array<double, k> integrate(const std::function<std::array<double, k> (const double &)> & f, const double & a, const double & b);
    template <std::size_t k> std::array<double, k> integrate(const std::function<std::array<double, k> (const double &)> & f, const double & a, const double & b, unsigned n);
    /// @}

    namespace integration
    {
        /*!
         * Set the default number of evaluations used by integrate().
         *
         * @param n      Number of evaluations, must be a power of 2 and no less than 16.
         */
        void set_n(unsigned n);

        /// Get the default number of evaluations used by integrate().
        unsigned get_n();

        /*!
         * InvalidNumberOfEvaluations is thrown when the parameter "n" passed to
         * integrate() or set_n() is less than 16 or not a power of 2.
         */
        struct InvalidNumberOfEvaluations :
            public Exception
        {
            ///@name Basic Functions
            ///@{
            /*!
             * Constructor.
             *
             * @param n The invalid argument passed for "n".
             */
            InvalidNumberOfEvaluations(unsigned n);
            ///@}
        };

        void validate(unsigned n);
    }
}

#endif
