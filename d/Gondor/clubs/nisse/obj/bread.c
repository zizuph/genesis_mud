/*
 *  /d/Gondor/clubs/nisse/obj/bread.c
 *
 *  Bacon and bread.
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
    
    set_name("bread");
    add_name(({"slab", "sandwich"}));
    set_short("slab of bread with bacon");
    set_pshort("slabs of bread with bacon");
    set_long("This sandwich is made from thick slices of smoked bacon on " +
        "a firm bread that seems more like a biscuit than bread. The bacon " +
        "is piled high on the bread making this a very filling sandwich.\n");

    set_amount(100);

    add_prop(OBJ_I_VALUE, 200);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}
