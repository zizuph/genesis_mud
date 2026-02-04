/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * boots.c
 *
 * Leather boots worn by orcs.
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
    set_name("boots");
    set_adj("new");
    set_short("pair of new boots");
    set_pshort("pairs of new boots");
    set_long("The leather is good quality.\n");
    set_ac(30);
    set_at(A_FEET);
    set_armour_size(SMALL);
    set_am(({0, 0, 0}));
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 3000);
}
