/* This comment tells emacs to use c++-mode  -*- C++ -*- */
/*
 * bskin.c
 *
 * Skin of a small bear
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
    set_adj(({"brown", "small"}));
    set_short("brown bearskin");
    set_long("This is a small brown bearskin. Taken from a recently killed "+
	     "bear.  From the size of the skin you guess that it is taken " +
	     "from a bearcub.");
    set_ac(1);
    set_at(A_ROBE);
    set_am(({0, -1, 1}));
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 2000);
}



