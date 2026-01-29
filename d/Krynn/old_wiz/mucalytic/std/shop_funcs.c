/* File that contains some shop functions. ~mucalytic/std/shop_funcs */

#include "/sys/money.h"
#include "/sys/composite.h"

/*
 * Function name: calculate_prices
 * Description:   Turns an integer amount of copper coins into a string
 *                description of this in pc, gc, sc, cc form.
 * Returns:       A string with of amounts of certain types of coin
 *                in the form 'Xpc, Xgc, Xsc and Xcc'.
 * Author:        Mucalytic.
 */
string calculate_prices(int coppers)
{
    int *money_array, i;
    string *type_array, *str_array, str;

    str_array  = ({ });
    type_array = ({ "cc", "sc", "gc", "pc" });

    money_array = MONEY_SPLIT(coppers);

    for(i = sizeof(money_array) - 1; i >= 0; i--)
    {
        if(money_array[i])
        {
            str = money_array[i] + type_array[i];
            str_array += ({ str });
        }
    }
    return(COMPOSITE_WORDS(str_array));
}
