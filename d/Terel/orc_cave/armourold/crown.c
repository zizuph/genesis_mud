/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * crown.c
 *
 * Worn by the orc chief.
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
    set_name("crown");
    set_adj("gold");
    set_short("gold crown");
    set_long("You examine the gold crown, but can't see whether it's fake " +
	     "or not.  Clearly it is very bad handwork.\n");
    set_ac(20);
    set_at(A_HEAD);
    set_am(({0, 0, 0}));
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 3000);
}
