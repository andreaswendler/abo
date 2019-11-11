#ifndef AVERAGE_CASE_ERROR_H
#define AVERAGE_CASE_ERROR_H

#include <vector>
#include <cudd/cplusplus/cuddObj.hh>
#include <boost/multiprecision/cpp_dec_float.hpp>

namespace abo::error_metrics {

    boost::multiprecision::cpp_dec_float_100 average_value(const std::vector<BDD> &f);

    boost::multiprecision::cpp_dec_float_100 mean_squared_value(const std::vector<BDD> &f);

    std::pair<boost::multiprecision::cpp_dec_float_100, boost::multiprecision::cpp_dec_float_100>
        average_relative_value(const Cudd &mgr, const std::vector<BDD> &f, const std::vector<BDD> &g);

    boost::multiprecision::cpp_dec_float_100 average_case_error(const Cudd &mgr, const std::vector<BDD> &f, const std::vector<BDD> &f_hat);

    boost::multiprecision::cpp_dec_float_100 mean_squared_error(const Cudd &mgr, const std::vector<BDD> &f, const std::vector<BDD> &f_hat);

    // compute the same values using an add as an intermediate step
    boost::multiprecision::cpp_dec_float_100 average_case_error_add(const Cudd &mgr, const std::vector<BDD> &f, const std::vector<BDD> &f_hat);

    boost::multiprecision::cpp_dec_float_100 mean_squared_error_add(const Cudd &mgr, const std::vector<BDD> &f, const std::vector<BDD> &f_hat);

}

#endif // AVERAGE_CASE_ERROR_H
