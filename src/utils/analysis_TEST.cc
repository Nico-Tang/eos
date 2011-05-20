/* vim: set sw=4 sts=4 et foldmethod=syntax : */

/*
 * Copyright (c) 2010, 2011 Frederik Beaujean
 * Copyright (c) 2011 Danny van Dyk
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

#include <src/utils/analysis_TEST.hh>

using namespace test;
using namespace eos;

class AnalysisTest :
    public TestCase
{
    public:
        AnalysisTest() :
            TestCase("analysis_test")
        {
        }

        virtual void run() const
        {
            static const double eps = 1e-13;

            // check cloning and values
            {
                Analysis analysis = make_analysis(false);

                auto clone1 = analysis.clone();
                auto clone2 = analysis.clone();

                // make sure observable's value is not equal to central value
                Parameter p = (*clone1)[0];
                p = 4.3; //posterior mode
                p = (*clone2)[0];
                p = 4.4; //log_prior mode

                // for comparison used ipython's log(scipy.stats.norm.pdf(4.3, loc=4.4, scale=0.1))
                // value at center of both Gaussian distributions. so pdf the same
                TEST_CHECK_RELATIVE_ERROR((*clone1->log_likelihood())(), +0.88364655978936768, eps);
                TEST_CHECK_RELATIVE_ERROR(clone1->log_prior(), 0.883646846442260436, eps);

                // almost, but not quite identical
                TEST_CHECK_RELATIVE_ERROR((*clone1->log_likelihood())(), clone1->log_prior(), 1e-6);

                TEST_CHECK_RELATIVE_ERROR((*clone2->log_likelihood())(), -0.61635344021063077, eps);

                TEST_CHECK_RELATIVE_ERROR(clone2->log_prior(), 1.38364684644226932, eps);


                // now change a parameter which is not scanned
                TEST_CHECK(analysis.parameters()["Abs{c7}"] != 2.599);
                analysis.parameters()["Abs{c7}"] = 2.599;
                AnalysisPtr clone3 = analysis.clone();

                TEST_CHECK_EQUAL(double(analysis.parameters()["Abs{c7}"] ),
                                 double( clone3->parameters()["Abs{c7}"] ));

            }

            // smart parameter adding
            {
                Parameters parameters = Parameters::Defaults();

                LogLikelihoodPtr llh(new LogLikelihood(parameters));
                llh->add(ObservablePtr(new TestObservable(parameters, Kinematics(),
                        "mass::b(MSbar)")), 4.1, 4.2, 4.3);
                Analysis analysis(llh);

                // store a clone with no parameters
                auto clone_bare = analysis.clone();


                // 4.4 +- 0.1
                analysis.add(LogPrior::Gauss(parameters, "mass::b(MSbar)",
                        ParameterRange
                            { 3.7, 4.9 }, 4.3, 4.4, 4.5));



                Parameter p = analysis[0];
                p = 4.3; //posterior mode


                TEST_CHECK_NEARLY_EQUAL((*analysis.log_likelihood())(), +0.88364655978936768, eps);
                TEST_CHECK_NEARLY_EQUAL(analysis.log_prior(), 0.883646846442260436, eps);
                // slightly different due to normalization of prior
                TEST_CHECK((*analysis.log_likelihood())() != analysis.log_prior());

                // now check cloning

                auto clone = analysis.clone();
                Parameter p2 = (*clone)[0];

                TEST_CHECK_EQUAL(double(p), double(p2));


                // change clone only
                p2 = 4.112;
                TEST_CHECK((*analysis.log_likelihood())() != (*clone->log_likelihood())());
                TEST_CHECK(analysis.log_prior() != clone->log_prior());

                // same value for clone and original
                p2 = 4.3;

                TEST_CHECK_EQUAL((*analysis.log_likelihood())(), (*clone->log_likelihood())());
                TEST_CHECK_EQUAL(analysis.log_prior(), clone->log_prior());
            }

            // nuisance properties.nuisance())
            {
                Analysis analysis = make_analysis(false);

                TEST_CHECK(!analysis.nuisance("mass::b(MSbar)"));

                analysis.add(LogPrior::Flat(analysis.parameters(), "mass::c", ParameterRange{ 1.4, 2.2}), true);

                TEST_CHECK(analysis.nuisance("mass::c"));
            }

            // stop if prior undefined
            {
                Parameters parameters = Parameters::Defaults();

                LogLikelihoodPtr llh(new LogLikelihood(parameters));
                llh->add(ObservablePtr(new TestObservable(parameters, Kinematics(),
                        "mass::b(MSbar)")), 4.1, 4.2, 4.3);
                Analysis analysis(llh);

                TEST_CHECK_THROWS(InternalError, analysis.log_prior());
            }
        }
} analysis_test;