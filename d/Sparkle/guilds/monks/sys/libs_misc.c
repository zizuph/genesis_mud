/*******************************************************************\
| LIBS_MISC.C                                                       |
+-------------------------------------------------------------------+
| Library functions that do not deserve a separate file.            |
\*******************************************************************/

/*
 * 06/08/16 Arandir     The random adjustment functions
 * 03/11/07 Arandir	The compare functions for sorting
 *
 */

#include "../defs.h"

//-------------------------------------------------------------------

/*******************************************************************\
| Helper functions for randomness.                                  |
\*******************************************************************/

/*
 * Function name : dg_random_adjust
 * Description   : Returns a random number close to an original value.
 *   fValue        : The value to randomize.
 *   fPrecision    : How many percents off.
 * Returns       : The random value.
 *
 */

float dg_random_adjust (float fValue, float fPrecision)
{
  float fLimit = fValue * fPrecision;
  float fChange = fLimit * rnd () * 2.0;
  return (fValue - fLimit + fChange);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Helper functions for sorting.                                     |
\*******************************************************************/

/*
 * Function name : dg_sort_int_ascending
 * Function name : dg_sort_int_descending
 *
 */

int dg_sort_int_ascending (mixed iA, mixed iB)
{
  return (iA - iB);
}

int dg_sort_int_descending (mixed iA, mixed iB)
{
  return (iB - iA);
}

//-------------------------------------------------------------------

