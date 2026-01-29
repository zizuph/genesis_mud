/*
 *  /d/Gondor/clubs/nisse/obj/meat.c
 *
 *  Smoked dried meat.
 *
 *  Deagol, March 2003
 */

inherit "/std/food";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_food()
{
    ::create_food();
    
    set_name("meat");
    set_pname("meats");
    set_adj("smoked");
    add_adj("dried");
    set_short("smoked dried meat");
    set_pshort("smoked dried meats");
    set_long("This strip of smoked dried meat is tasty, filling and chewy. " +
        "You are not sure what kind of meat this is, it could be beef, " +
        "pork or turkey. The smoking flavour is all that you can really " +
        "make out.\n");

    set_amount(350);

    add_prop(OBJ_I_VALUE, 1200);
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 400);
}

/*
 *  Function name: special_effect
 *  Description  : This routine is called when a player eats the cram.
 *  Arguments    : int amnt - amount of food
 */
public void
special_effect(int amnt)
{
    write("The smoking aroma rests on your tongue. You recognize " +
        "the meat is permeated with the flavour of smoked " +
        one_of_list(({"beech", "hickory", "oaken", "apple"})) + " wood.\n");
}
