#pragma once

#include <vector>
#include <cudd/cplusplus/cuddObj.hh>
#include <boost/multiprecision/cpp_dec_float.hpp>

#include "number_representation.hpp"

namespace abo::error_metrics {

    using abo::util::NumberRepresentation;

    /**
     * @brief Computes bounds on the average relative difference between f and f_hat
     * It is defined as the average of |f(x) - f_hat(x)| / max(1, |f(x)|) for all inputs x
     * As it is not symmetric, it is not a metric in the mathematical sense
     * This function returns a range in which the actual average relative error is guaranteed to lie
     * The computed bounds are always within a factor of 2, meaning that the maximum error
     * returned by this function is at most twice the minimum error
     * @param mgr The BDD object manager
     * @param f The original function
     * @param f_hat The approximated function. Must have the same number of bits as f
     * @param num_rep The number representation for f and f_hat
     * @return {min, max}, the lower and upper bound on the average case relative error
     */
    std::pair<boost::multiprecision::cpp_dec_float_100, boost::multiprecision::cpp_dec_float_100>
        average_relative_error_bounds(const Cudd &mgr, const std::vector<BDD> &f, const std::vector<BDD> &f_hat,
                                      const NumberRepresentation num_rep = NumberRepresentation::BaseTwo);

    /**
     * @brief Computes the average relative difference between f and f_hat
     * It is defined as the average of |f(x) - f_hat(x)| / max(1, |f(x)|) for all inputs x
     * As it is not symmetric, it is not a metric in the mathematical sense
     * The computation is performed with ADDs and might be quite slow
     * @param mgr The BDD object manager
     * @param f The original function
     * @param f_hat The approximated function. Must have the same number of bits as f
     * @param num_rep The number representation for f and f_hat
     * @return the average relative difference of the inputs
     */
    boost::multiprecision::cpp_dec_float_100 average_relative_error_add(const Cudd &mgr, const std::vector<BDD> &f, const std::vector<BDD> &f_hat,
                                                                        const NumberRepresentation num_rep = NumberRepresentation::BaseTwo);

    /**
     * @brief Computes the average relative difference between f and f_hat
     * It is defined as the average of |f(x) - f_hat(x)| / max(1, |f(x)|) for all inputs x
     * As it is not symmetric, it is not a metric in the mathematical sense
     * The computation is performed with BDDs using a symbolic division and might be quite slow
     * @param mgr The BDD object manager
     * @param f The original function
     * @param f_hat The approximated function. Must have the same number of bits as f
     * @param num_extra_bits The number of additional fixed precision bits to use during the division
     * As the result of each division is not an integer, the result is described as a fixed point number
     * with exactly num_extra_bits bits with a lower significance than one. Roughly correlates the the precision of the result
     * @param num_rep The number representation for f and f_hat
     * @return the average relative difference of the inputs
     */
    boost::multiprecision::cpp_dec_float_100 average_relative_error_symbolic_division(const Cudd &mgr, const std::vector<BDD> &f, const std::vector<BDD> &f_hat,
                                                                                      unsigned int num_extra_bits = 16,
                                                                                      const NumberRepresentation num_rep = NumberRepresentation::BaseTwo);
}
