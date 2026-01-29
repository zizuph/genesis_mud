/*
 *  /d/Gondor/clubs/nisse/obj/cookies.c
 *
 *  A small sack of mincemeat cookies.
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
    
    set_name("cookies");
    add_name(({"sack", "cookie"}));
    set_adj("small");
    set_short("small sack of mincemeat cookies");
    set_pshort("small sacks of mincemeat cookies");
    set_long("You notice this cookie is cooked on a grill instead of in " +
        "an oven, which is why it is browned on both the top and bottom. " +
        "You can see the bits of mincemeat embedded into the cookie. The " +
        "cookies are dry but tasty.\n");

    set_amount(150);

    add_prop(OBJ_I_VALUE, 220);
    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 150);
}

/*
 *  Function name: special_effect
 *  Description  : This routine is called when a player eats the cookies
 *  Arguments    : int amnt - amount of food
 */
public void
special_effect(int amnt)
{
    write("The cookies crack between your teeth.\n");
}
