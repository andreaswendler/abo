//
// Created by keszocze on 21.09.18.
//

#include <pla_parser.hpp>
#include <cudd_helpers.hpp>
#include <cudd/cplusplus/cuddObj.hh>
#include <catch2/catch.hpp>

using namespace abo;
using namespace abo::util;


TEST_CASE("parse or.pla file") {

    Cudd mgr(2);


    std::vector<std::string> innames;
    std::vector<std::string> outnames;
    std::vector<BDD> out;

    abo::parser::pla_parser parser(mgr, out, innames, outnames);

    lorina::read_pla("or.pla", parser);

    REQUIRE(innames.size() == 2);
    REQUIRE(outnames.size() == 1);
    REQUIRE(out.size() == 1);

    // explicitly check the names

    // these can be retrieved multiple ways
    REQUIRE(innames[0] == "a");
    REQUIRE(innames[1] == "b");
    REQUIRE(mgr.getVariableName(0) == "a");
    REQUIRE(mgr.getVariableName(1) == "b");

    REQUIRE(outnames[0] == "f");


    REQUIRE(out[0].nodeCount() == 3); // it seems that you do count the terminal node
    REQUIRE(mgr.nodeCount(out) == 3);

    // number of variables in total
    REQUIRE(Cudd_ReadSize(mgr.getManager()) == 2);

    // number of variables on that particular output
    REQUIRE(out[0].SupportSize() == 2);


}

TEST_CASE("parse funs.pla and perform basic operations") {
    Cudd mgr(2);


    std::vector<std::string> innames;
    std::vector<std::string> outnames;
    std::vector<BDD> out;

    abo::parser::pla_parser parser(mgr, out, innames, outnames);

    lorina::read_pla("funs.pla", parser);

    REQUIRE(innames.size() == 2);
    REQUIRE(outnames.size() == 3);
    REQUIRE(out.size() == 3);


    // explicitly check the names
    REQUIRE(innames[0] == "x");
    REQUIRE(innames[1] == "y");
    REQUIRE(mgr.getVariableName(0) == "x");
    REQUIRE(mgr.getVariableName(1) == "y");

    REQUIRE(outnames[0] == "or");
    REQUIRE(outnames[1] == "and");
    REQUIRE(outnames[2] == "id_y");

    REQUIRE(out[0].nodeCount() == 3); // it seems that you do count the terminal node
    REQUIRE(out[1].nodeCount() == 3); // it seems that you do count the terminal node
    REQUIRE(out[2].nodeCount() == 2);
    REQUIRE(mgr.nodeCount(out) == 4);

    // number of variables in total
    REQUIRE(Cudd_ReadSize(mgr.getManager()) == 2);

    // number of variables on that particular output
    REQUIRE(out[0].SupportSize() == 2);
    REQUIRE(out[1].SupportSize() == 2);
    REQUIRE(out[2].SupportSize() == 1);

}

TEST_CASE("check handling of overlapping cubes in pla specification") {
    Cudd mgr(2);
    std::vector<std::string> innames;
    std::vector<std::string> outnames;
    std::vector<BDD> out;

    abo::parser::pla_parser parser(mgr, out, innames, outnames);

    lorina::read_pla("dc.pla", parser);

    int assignments[4][2] = {
            {0, 0},
            {0, 1},
            {1, 0},
            {1, 1}
    };
    bool expected_values[4] = {true, false, true, true};

    for (unsigned int i = 0; i < 4; i++) {

        REQUIRE(out.at(0).Eval(assignments[i]).IsOne() == expected_values[i]);

    }


}