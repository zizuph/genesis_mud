/*
   /d/Gondor/clubs/storyteller/obj/std_food.c
   
   This is the standard object used for any form of eatable things
   in the storytellers, stolen from /std/food.c.

   Typical usage of /std/food.c

        inherit "/std/food";

        void
        create_food()
        {
            set_amount(amount_in_gram);
            set_name("name of food");
            set_short(...);
            set_long(....);
        }

    If you want any special effect in your food you can define
    special_effect() which is called when eating it.
    The number of items you ate is passed as argument to special_effect();

    Food may recover and recovery is added by default, but only if the
    the food has been coded in a particular object and not cloned from
    this file directly and externally set up.
*/

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <macros.h>
#include <stdproperties.h>

/*
 * Global variables. They are not saved.
 */
static  int     food_amount;

/*
 * Prototype.
 */
public void special_effect(int amount);

/*
 * Function name: create_food
 * Description  : This function is the constructor. You should redefine
 *                it to create your own food object.
 */
public void
create_food()
{
}

public nomask void
create_object()
{
    add_prop(OBJ_M_NO_SELL, "Food is not to be resold.\n");

    set_name("food");
    set_pname("foods");

    create_food();
}

/*
 * Function name: set_short
 * Description  : When the short is set/changed, also make sure that we do set
 *                the unique identifier for the heap.
 * Arguments    : mixed new_short - the short description.
 */
void
set_short(mixed new_short)
{
    ::set_short(new_short);

}

/*
 * Function name:       set_amount
 * Description:         sets the amount of food in this food (in grams)
 * Arguments:           a: The amount of food
 */
public void
set_amount(int a) 
{ 
    food_amount = a; 
    add_prop(OBJ_I_VOLUME, a / 10);
    add_prop(OBJ_I_WEIGHT, a);
}

/*
 * Function name:       query_amount
 * Description:         Gives the amount of food in this food
 * Returns:             Amount as int (in grams)
 */
public int
query_amount() { return food_amount; }

/*
 * Function name: eat_me
 * Description:   eat this food
 * Returns:       string - an error message (failure)
 *                1 - food successfully eaten
 */
public mixed
command_eat()
{
    int am, num, i;

    am = query_amount();

    if (!this_player()->eat_food(am))
    {
        return "The " + short() + " is too much for you.\n";
    }

    special_effect(i);
    return 1;
}

/*
 * Function name: remove_food
 * Description:   Reduce the number of items in this heap after a split_heap()
 *                or remove the heap if there are no items left.
 */
public void
remove_food()
{
    remove_object();
}

/*      
 * Function name: special_effect
 * Description  : Define this routine if you want to do some special effect
 *                if a player consumes this food.
 * Arguments    : int amount - the number of foods consumed.
 */             
public void
special_effect(int amount)
{
}
