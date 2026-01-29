/*
 * Roast Pig - /d/Gondor/rhovanion/dolguldur/obj/pig.c
 *
 * Varian - November 2020
 */

#pragma strict_types

#include <stdproperties.h>

inherit "/std/food";

void
create_food() 
{
    set_name( ({"pig", "roast pig", "roast"}) );
    set_pname( ({"pigs", "roast pigs", "roasts"}) );
    set_short("roast pig");
    set_pshort("roast pigs");
    set_long("This is a suculent roast pig, undoubtedly " +
        "caught in the depths of Mirkwood forest.\n");
    set_amount(575);
    add_prop(OBJ_I_WEIGHT,750);
    add_prop(OBJ_I_VOLUME,900);
    add_prop(OBJ_I_VALUE, 500);
}