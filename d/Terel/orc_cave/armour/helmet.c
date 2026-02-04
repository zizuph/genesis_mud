/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * helmet.c
 *
 * Clap helmet.  Worn by orcs.
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
    set_name("helmet");
    set_adj("clap");
    set_short("clap helmet");
    set_long("This clap helmet comes from the far north.  "+
	     "It is possible to distinguish clap helmets from other helmets "+
	     "because they have two silly looking hands on each side.\n");
    set_ac(30);
    set_at(A_HEAD);
    set_armour_size(SMALL);
    set_am(({0, 0, 0}));
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 3000);
}
