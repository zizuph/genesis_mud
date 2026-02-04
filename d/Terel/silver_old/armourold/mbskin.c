/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * bskin.c
 *
 * Skin of a male bear
 */

#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

#include "/d/Terel/include/recover.h"
#include <wa_types.h>

/*
 * Function name: create_armour
 * Description:   Reset the armour
 */
public void
create_armour()
{
    ::create_armour();
    set_name("bearskin");
    set_adj("brown");
    set_short("large brown bearskin");
    set_long("This is a brown bearskin. Taken from a recently killed bear. " +
	     "From the markings on the skin you see that it is taken from " +
	     "a large male.\n");
    set_ac(5);
    set_at(A_ROBE);
    set_am(({-1, 0, 1}));
    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VOLUME, 8000);
}



