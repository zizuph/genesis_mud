/* This comment tells emacs to use c++-mode  -*- C++ -*- */
/*
 * bskin.c
 *
 * Skin of a female bear
 * Updated by Shinto to reflect changes in Terel STDARMOUR
 */

#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

#include <wa_types.h>

/*
 * Function name: create_armour
 * Description:   Reset the armour
 */
public void
create_terel_armour()
{
    set_name("bearskin");
    set_adj("brown");
    set_short("brown bearskin");
    set_long("This is a brown bearskin. Taken from a recently killed bear.  " +
	     "From the markings on the skin you see that it is taken from a " +
	     "female.\n");
    set_ac(4);
    set_at(A_ROBE);
    set_am(({-1, 0, 1}));
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 5000);
}


