/*
 * Calculations
 *
 * Created by Petros, April 2011
 */

#pragma strict_types

#include <math.h>

/*
 * Function:    convert_to_float
 * Description: Converts an array of numbers to an array of floats
 */
private float *
convert_to_float(mixed * numbers)
{
    float * float_numbers = ({ });
    foreach (mixed number : numbers)
    {
        if (intp(number))
        {
            float_numbers += ({ itof(number) });
        }
        else if (floatp(number))
        {
            float_numbers += ({ number });
        }
        else
        {
            throw("Invalid input to average function.\n");
        }
    }
    
    return float_numbers;
}

/*
 * Function:    average_helper
 * Description: This is a helper function that takes in an array of
 *              floats and calculates the average. It is used by the
 *              interface "average" function.
 */
private float
average_helper(float * numbers)
{
    return SUM_ARRAY(numbers) / itof(sizeof(numbers));
}

/*
 * Function:    average
 * Description: Given an array of numbers, it returns the average. You
 *              can pass both ints and floats
 */
public float
average(mixed * numbers)
{
    float * float_numbers = convert_to_float(numbers);
    if (!sizeof(float_numbers))
    {
        return 0;
    }
    
    return average_helper(float_numbers);;
}

/*
 * Function:    square_distance
 * Description: Calculates the square of the distance from the average.
 *              Used by the standard_deviation calculation.
 */
private float
square_distance(float f, float avg)
{
    f = f - avg;
    return f * f;
}

/*
 * Function:    standard_deviation
 * Description: This calculates the standard deviation of a list of numbers.
 *              You can pass either integers or floats.
 */
public float
standard_deviation(mixed * numbers)
{
    float * float_numbers = convert_to_float(numbers);
    if (!sizeof(float_numbers) || sizeof(float_numbers) == 1)
    {
        return 0;
    }
    
    // Calculating the standard deviation means taking the
    // following steps
    // 1. Calculate the average (mean)
    // 2. Create an array of the square of the distance of each number from the average
    // 3. Take an average of the array in step 2 with one degree loss of freedom (ie. divide by one less than the total number of items)
    // 4. Take the square root of the average in step 3.
    float avg = average_helper(float_numbers); // Step 1
    float * square_distances = map(float_numbers, &square_distance(,avg)); // Step 2
    // Steps 3 and 4
    
    return pow(SUM_ARRAY(square_distances) / (itof(sizeof(square_distances)) - 1.0), 0.5);
}
