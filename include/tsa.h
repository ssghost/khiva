// Copyright (c) 2018 Grumpy Cat Software S.L.
// 
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include "version.h"
#include <vector>

using namespace af;


namespace tsa {
    
    const char* version();

    namespace simplification {

       /**
         * @brief Definition of Point structure to represent 2D points
         */
        typedef std::pair<double, double> Point;
        
        /**
         * @brief Simplifies a set of points by applying the RamerDouglasPeucker method 
         * depending on the perpendicular distance of the points and epsilon, the greater epsilon,
         * ore points are deleted.
         * 
         * @param epsilon It acts as  the threshold value to decide which points should be considered
         * meaningful or not.
         * 
         * @return array Array with the same dimensions as tss where the time series have been
         * adjusted for zero mean and one as standard deviation.
         */
        std::vector<tsa::simplification::Point> ramerDouglasPeucker(std::vector<tsa::simplification::Point> pointList, double epsilon);
        
        /**
         * @brief Simplifies a set of points by applying the RamerDouglasPeucker method 
         * depending on the perpendicular distance of the points and epsilon, the greater epsilon,
         * ore points are deleted.
         * 
         * @param epsilon It acts as  the threshold value to decide which points should be considered
         * meaningful or not.
         * 
         * @return array Array with the same dimensions as tss where the time series have been
         * adjusted for zero mean and one as standard deviation.
         */
        array ramerDouglasPeucker(array pointList, double epsilon);

        /**
         * @brief Simplifies a set of points by applying the visvalingam method (minimun triangle area) 
         * until the number of points is reduced to @num_points_allowed.
         * 
         * @param pointList Expects an input array whose dimension zero is the length of the time 
         * series.
         * 
         * @param numPoints Sets the number of points in pointList after the execution of the method.
         * 
         * @return a vector with the same dimensions as poinList where the number of points has been 
         * reduced up to numPoints.
         */
        std::vector<tsa::simplification::Point> visvalingam_simplify(std::vector<tsa::simplification::Point> pointList, int numPoints);

         /**
         * @brief Simplifies a set of points by applying the visvalingam method (minimun triangle area) 
         * until the number of points is reduced to @num_points_allowed.
         * 
         * @param pointList Expects an input array whose dimension zero is the length of the time 
         * series.
         * 
         * @param numPoints Sets the number of points in pointList after the execution of the method.
         * 
         * @return a vector with the same dimensions as poinList where the number of points has been 
         * reduced up to numPoints.
         */
        array visvalingam_simplify(array pointList, int numPoints);          
    };

    namespace regularization {
        // array xyz(array source);
    }

    namespace normalization {
        /**
         * @brief Calculates a new set of timeseries with zero mean and 
         * standard deviation one.
         * 
         * @param tss Expects an input array whose dimension zero is the length of the time 
         * series (all the same) and dimension one indicates the number of 
         * time series.
         * 
         * @param epsilon Minimum standard deviation to consider.  It acts a a gatekeeper for
         * those time series that may be constant or near constant.  
         * 
         * @return af::array Array with the same dimensions as tss where the time series have been
         * adjusted for zero mean and one as standard deviation.
         */
        af::array znorm(af::array tss, double epsilon = 0.00000001);

        /**
         * @brief Adjusts the time series in the given input and performs z-norm 
         * inplace (without allocating further memory)
         * 
         * @param tss Expects an input array whose dimension zero is the length of the time 
         * series (all the same) and dimension one indicates the number of 
         * time series.
         * 
         * @param epsilon Minimum standard deviation to consider.  It acts a a gatekeeper for
         * those time series that may be constant or near constant.  
         */
        void znormInPlace(af::array &tss, double epsilon = 0.00000001);

        /**
         * @brief Normalizes the given time series according to its minimum and maximun value and 
         * adjusts each value within the range [low, high]
         * 
         * @param tss Expects an input array whose dimension zero is the length of the time 
         * series (all the same) and dimension one indicates the number of 
         * time series.
         * 
         * @param high Maximum final value.  Defaults to 1.0
         * @param low  Minimum final value.  Defaults to 0.0
         * 
         * @param epsilon Safeguard for constant (or near constant) time series as the operation implies
         * a unit scale operation between min and max values in the tss.
         * 
         * @return af::array An array with the same dimensions as tss, whose values (time series in dimension 0)
         * have been normalized by maximun and minimun values, and scaled as per high and low parameters.
         */
        af::array maxMinNorm(af::array tss, double high = 1.0, double low = 0.0, double epsilon = 0.00000001);

        /**
         * @brief Same as maxMinNorm, but it performs the operation in place, without allocating further memory.
         * 
         * @param tss Expects an input array whose dimension zero is the length of the time 
         * series (all the same) and dimension one indicates the number of 
         * time series.
         * 
         * @param high Maximum final value.  Defaults to 1.0
         * @param low  Minimum final value.  Defaults to 0.0
         * 
         * @param epsilon Safeguard for constant (or near constant) time series as the operation implies
         * a unit scale operation between min and max values in the tss.
         */
        void maxMinNormInPlace(af::array &tss, double high = 1.0, double low = 0.0, double epsilon = 0.00000001);

        /**
         * @brief Normalizes the given time series according to its maximun value and 
         * adjusts each value within the range (-1, 1)
         * 
         * @param tss Expects an input array whose dimension zero is the length of the time 
         * series (all the same) and dimension one indicates the number of time series.
         * 
         * @return af::array An array with the same dimensions as tss, whose values (time series in dimension 0)
         * have been normalized by dividing each number by 10^j, where j is the number of integer digits of 
         * the max number in the timeseries
         */
        af::array decimalScalingNorm(af::array tss);

        /**
         * @brief Same as decimalScalingNorm, but it performs the operation in place, without allocating further
         *  memory.
         * 
         * @param tss Expects an input array whose dimension zero is the length of the time 
         * series (all the same) and dimension one indicates the number of time series.
         */
        void decimalScalingNormInPlace(af::array &tss);

        // adaptive normalization
    };

    namespace features {

        af::array absEnergy(af::array);

        void absEnergyInPlace(af::array);
        // tsfresh
        /**
         * @brief Calculates the sum over the absolute value of consecutive changes in the time series
         * 
         * @param tss Expects an input array whose dimension zero is the length of the time 
         * series (all the same) and dimension one indicates the number of 
         * time series.
         * @return af::array An array with the same dimensions as tss, whose values (time series in dimension 0)
         * contains absolute value of consecutive changes in the time series
         */
        af::array absoluteSumOfChanges(af::array tss);
        
        // PIP Perceptualy important points
    };

    namespace dimensionality {
        
        /**
         * @brief Piecewise Aggregate Approximation. It reduces the dimensionality of the timeseries
         * given by @begin and @last iterators to a number equal to bins. This algorithim divides the
         * whole timeseries in @bins partitions and computes the average of each partition
         * 
         * @param begin iterator to the first element
         * 
         * @param last iterator to the last element
         * 
         * @param bins sets the total number of divisions
         * 
         * @return result A vector with the reduced dimensionality.
         */
        af::array PAA(af::array a, int bins);

        /**
         * @brief Piecewise Aggregate Approximation. It reduces the dimensionality of the timeseries
         * given by @begin and @last iterators to a number equal to bins. This algorithim divides the
         * whole timeseries in @bins partitions and computes the average of each partition
         * 
         * @param begin iterator to the first element
         * 
         * @param last iterator to the last element
         * 
         * @param bins sets the total number of divisions
         * 
         * @return result A vector with the reduced dimensionality.
         */
        template <class InputIt>
        std::vector<tsa::simplification::Point> PAA_CPU(InputIt begin, InputIt last, int bins){

            double xrange = (*(last-1)).first - (*begin).first;
            double width_bin = xrange / bins;
            double reduction = bins / xrange;

            std::vector<double> sum(bins, 0.0);
            std::vector<int> counter(bins, 0);
            std::vector<tsa::simplification::Point> result(bins, tsa::simplification::Point(0.0, 0.0));
            
            //Iterating over the  timeseries
            for(auto i = begin; i != last; i++){
                int pos = std::min((*i).first * reduction, (double) (bins-1));
                sum[pos] += (*i).second;
                counter[pos] = counter[pos] + 1;
            }

            //Compute the average per bin
            for(int i = 0; i < bins; i++){
                result[i].first = (width_bin * i) + (width_bin / 2.0);
                result[i].second = sum[i] / counter[i];
            }
            return result;
        }

        /**
         * @brief Symbolic Aggregate approXimation. It transforms a numeric timeseries into
         * a timeseries of symbols with the same size.
         * 
         * @param a, array with the input timeseries
         * 
         * @param alphabet_size, number of element within the alphabet
         * 
         * @return result An array of symbols.
         */
        std::vector<int> SAX(array a, int alphabet_size);

        // PAA/PLA
        // SAX
        // Principal Components A.
        // Random Projections
    };

    namespace distances {

        /**
         * @brief Calculates euclidean distances between timeseries.  
         * 
         * @param tss Expects an input array whose dimension zero is the length of the time 
         * series (all the same) and dimension one indicates the number of 
         * time series.
         * 
         * @return array Returns an upper triangular matrix where each position corresponds to the 
         * distance between two time series. Diagonal elements will be zero.  For example: 
         * Position row 0 column 1 will record the distance between time series 0 
         * and time series 1.
         */
        af::array euclidean(af::array tss);

        /**
         * @brief Calculates non squared version of the euclidean distance.
         * 
         * @param tss Expects an input array whose dimension zero is the length of the time 
         * series (all the same) and dimension one indicates the number of 
         * time series.
         * 
         * @return array Returns an upper triangular matrix where each position corresponds to the 
         * distance between two time series. Diagonal elements will be zero.  For example: 
         * Position row 0 column 1 will record the distance between time series 0 
         * and time series 1.
         */
        af::array squaredEuclidean(af::array tss);

        // habituales + la ncc

        // una funcion que dada un tipo de destiancia retorna 
        // una matriz triangular de distancias entre timeseries 
    };

    namespace matrix {
        /**
         * @brief Calculates the sliding dot product of the time series 'q' against t
         * 
         * @param q Array whose first dimension is the length of the query time series
         * and the last dimension is the number of time series to calculate
         * @param t Array with the second time series in the first dimension
         * @return array Returns an array with as many elements as 't' in the first dimension
         * and as many elements as the last dimension of 'q' in the last dimension
         */
        af::array slidingDotProduct(af::array q, af::array t);

        /**
         * @brief Calculates the moving average and standard deviation of the time series 't'.
         * 
         * @param t Input time series. Multiple time series 
         * @param a Auxiliary array to be used in the function calculateDistanceProfile. Use
         * the overloaded method without this parameter
         * @param m Window size
         * @param mean Output array containing the moving average
         * @param stdev Output array containing the moving standard deviation
         */
        void meanStdev(af::array t, af::array &a, long m, af::array &mean, af::array &stdev);

        /**
         * @brief Calculates the moving average and standard deviation of the time series 't'.
         * 
         * @param t Input time series. Multiple time series 
         * @param m Window size
         * @param mean Output array containing the moving average
         * @param stdev Output array containing the moving standard deviation
         */
        void meanStdev(af::array t, long m, af::array &mean, af::array &stdev);

        /**
         * @brief Function to generate a band matrix of batchSizeXtsLength with the offset batchStart
         * 
         * @param m Subsequence length used to generate a band of m/2 at each side
         * @param batchSize size of the first dimension
         * @param batchStart offset of the band matrix
         * @param tsLength size of the second dimension of the matrix
         * @return af::array 
         */
        af::array generateMask(long m, long batchSize, long batchStart, long tsLength);
        
        /**
         * @brief Calculates the distance between 'q' and the time series 't', which produced the sliding. Multiple queries can
         * be computed simultaneously in the last dimension of 'q'.
         * @param m Subsequence length (required to mask the minimum m/2 positions left and right in case ignoreTrivial is true)
         * @param qt The sliding dot product of 'q' and 't'
         * @param a Auxiliary array computed using the meanStdev function. This array contains a
         * precomputed fixed value to speed up the distance calculation 
         * @param sum_q Sum of the values contained in 'q'
         * @param sum_q2 Sum of squaring the values contained in 'q'
         * @param mean_t Moving average of 't' using a window size equal to the number of elements
         * in 'q'
         * @param sigma_t Moving standard deviation of 't' using a window size equal to the number of elements
         * in 'q'
         * @param mask Mask band matrix to filter the trivial match of a subsequence with itself
         * @param distance Resulting minimal distance
         * @param index Position where the minimum is occurring
         * @param batchStart Indicates where the currently computed batch starts. Defaults to 0 for the parallel case. The parameter
         * is used to determine the mask for the trivial matches.
         */
        void calculateDistanceProfile(long m, af::array qt, af::array a,
                                af::array sum_q, af::array sum_q2, af::array mean_t, af::array sigma_t, af::array mask,
                                af::array &distance, af::array &index);

        /**
         * @brief Calculates the distance between 'q' and the time series 't', which produced the sliding. Multiple queries can
         * be computed simultaneously in the last dimension of 'q'.
         * @param m Subsequence length (required to mask the minimum m/2 positions left and right in case ignoreTrivial is true)
         * @param qt The sliding dot product of 'q' and 't'
         * @param a Auxiliary array computed using the meanStdev function. This array contains a
         * precomputed fixed value to speed up the distance calculation 
         * @param sum_q Sum of the values contained in 'q'
         * @param sum_q2 Sum of squaring the values contained in 'q'
         * @param mean_t Moving average of 't' using a window size equal to the number of elements
         * in 'q'
         * @param sigma_t Moving standard deviation of 't' using a window size equal to the number of elements
         * in 'q'
         * @param distance Resulting minimal distance
         * @param index Position where the minimum is occurring
         */
        void calculateDistanceProfile(long m, af::array qt, af::array a,
                                af::array sum_q, af::array sum_q2, af::array mean_t, af::array sigma_t,
                                af::array &distance, af::array &index);

        /**
         * @brief 
         * 
         * @param q Array whose first dimension is the length of the query time series
         * and the last dimension is the number of time series to calculate
         * @param t Array with the second time series in the first dimension
         * @param m Subsequence length (required to mask the minimum m/2 positions left and right in case ignoreTrivial is true)
         * @param a Auxiliary array computed using the meanStdev function. This array contains a
         * precomputed fixed value to speed up the distance calculation
         * * @param mean_t Moving average of 't' using a window size equal to the number of elements
         * in 'q'
         * @param sigma_t Moving standard deviation of 't' using a window size equal to the number of elements
         * in 'q'
         * @param ignoreTrivial Boolean value that indicates whether the function should consider the trivial match of
         * a subsequence with itself or not
         * @param distance Resulting minimal distance
         * @param index Position where the minimum is occurring
         */
        void mass(af::array q, af::array t, long m, af::array a, af::array mean_t, af::array sigma_t, af::array mask,
                    af::array &distance, af::array &index);

        /**
         * @brief 
         * 
         * @param q Array whose first dimension is the length of the query time series
         * and the last dimension is the number of time series to calculate
         * @param t Array with the second time series in the first dimension
         * @param m Subsequence length (required to mask the minimum m/2 positions left and right in case ignoreTrivial is true)
         * @param a Auxiliary array computed using the meanStdev function. This array contains a
         * precomputed fixed value to speed up the distance calculation
         * * @param mean_t Moving average of 't' using a window size equal to the number of elements
         * in 'q'
         * @param sigma_t Moving standard deviation of 't' using a window size equal to the number of elements
         * in 'q'
         * @param distance Resulting minimal distance
         * @param index Position where the minimum is occurring
         */
        void mass(af::array q, af::array t, long m, af::array a, af::array mean_t, af::array sigma_t, af::array &distance, af::array &index);

        /**
         * @brief STAMP algorithm to calculate the matrix profile between 'ta' and 'tb' using a subsequence length
         * of 'm'
         * 
         * @param ta Query time series
         * @param tb Reference time series
         * @param m Subsequence length
         * @param profile The matrix profile, which reflects the distance to the closer element of the subsequence
         * from 'ta' in 'tb'
         * @param index The matrix profile index, which points to where the previously mentioned minimum is located
         */
        void stomp(af::array ta, af::array tb, long m, af::array &profile, af::array &index);

        /**
         * @brief STAMP algorithm to calculate the matrix profile between 't' and itself using a subsequence length
         * of 'm'. This method filters the trivial matches.
         * 
         * @param t Query and reference time series
         * @param m Subsequence length
         * @param profile The matrix profile, which reflects the distance to the closer element of the subsequence
         * from 't' in a different location of itself
         * @param index The matrix profile index, which points to where the previously mentioned minimum is located
         */
        void stomp(af::array t, long m, af::array &profile, af::array &index);

        /**
         * @brief This function extracts the best N motifs from a previously calculated matrix profile
         * 
         * @param profile The matrix profile containing the minimum distance of each subsequence
         * @param index The matrix profile index containing where each minimum occurs
         * @param n Number of motifs to extract
         * @param motifs The distance of the best N motifs
         * @param motifsIndices The indices of the best N motifs
         * @param subsequenceIndices The indices of the query sequences that produced the minimum reported in the motifs
         * output array
         */
        void findBestNMotifs(af::array profile, af::array index, long n, af::array &motifs, af::array &motifsIndices, af::array &subsequenceIndices);

        /**
         * @brief This function extracts the best N discords from a previously calculated matrix profile
         * 
         * @param profile The matrix profile containing the minimum distance of each subsequence
         * @param index The matrix profile index containing where each minimum occurs
         * @param n Number of discords to extract
         * @param discords The distance of the best N discords
         * @param discordIndices The indices of the best N discords
         * @param subsequenceIndices The indices of the query sequences that produced the discords reported in the discords
         * output array
         */
        void findBestNDiscords(af::array profile, af::array index, long n, af::array &discords, af::array &discordsIndices, af::array &subsequenceIndices);
        
        #ifdef __cplusplus
        extern "C"{
        #endif
        
        /**
         * @brief  Primitive for calling the STAMP algorithm to calculate the matrix profile between 'ta' and 'tb' using a subsequence length
         * of 'm'.
         * 
         * @param ta Pointer of an array of doubles with the first time series values.
         * @param tb Pointer of an array of doubles with the second time series values.
         * @param lta Pointer to an integer with the length of the first time series. 
         * @param ltb Pointer to an integer with the length of the second time series.
         * @param m Pointer to a long with the length of the subsequence.
         * @param p Pointer to an initialized array of doubles for storing the distance profile.
         * @param i Pointer to an initialized array of doubles for storing the index profile.
         */
        void stomp(double* ta, double* tb, int* lta, int* ltb, long*m, double* p, unsigned int* i);
        
        /**
         * @brief Primitive for calling the STAMP algorithm to calculate the matrix profile between 't' and itself using a subsequence length
         * of 'm'. This method filters the trivial matches.
         * 
         * @param ta Pointer of an array of doubles with the first time series values.
         * @param lta Pointer to an integer with the length of the first time series.
         * @param m Pointer to a long with the length of the subsequence.
         * @param p Pointer to an initialized  array of doubles for storing the distance profile.
         * @param i Pointer to an initialized  array of doubles for storing the index profile.
         */
        void stomp_self_join(double* ta, int* lta, long*m, double* p, unsigned int* i);

        #ifdef __cplusplus
        }
        #endif
       
    };

    namespace stats {
        /**
         * @brief Cumulative density function (CDF) of a standard normal (Gaussian) random variable
         * 
         * @param x The random variable
         * @return double The CDF value
         */
        double cdf(double x);
    };
};

