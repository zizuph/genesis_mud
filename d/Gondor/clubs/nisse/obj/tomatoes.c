/*
 *  /d/Gondor/clubs/nisse/obj/tomatoes.c
 *
 *  A green tomatoes.
 *
 *  Deagol, April 2003
 */

inherit "/std/food";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_food()
{
    ::create_food();
    
    set_name("tomatoes");
    add_name("tomato");
    set_adj(({"half", "dozen", "of", "green"}));
    set_short("half dozen of green tomatoes");
    set_pshort("half dozens of green tomatoes");
    set_long("These small green tomatoes make a perfect food for a long " +
        "journey. They are tiny, hard and last for days. Although slightly " +
        "bitter, they provide a good vegetable for the road.\n");

    set_amount(180);

    add_prop(OBJ_I_VALUE, 200);
    add_prop(OBJ_I_WEIGHT, 180);
    add_prop(OBJ_I_VOLUME, 180);
}

/*
 *  Function name: special_effect
 *  Description  : This routine is called when a player eats the cram.
 *  Arguments    : int amnt - amount of food
 */
public void
special_effect(int amnt)
{
    write("You manage all six green tomatoes at once. They stuffed your " +
        "stomach pretty much.\n");
}
