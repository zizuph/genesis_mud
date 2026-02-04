/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * ogre_boots.c
 *
 * a pair of ogre-sized boots
 *
 * Goldberry April, 2000
 */

#include <wa_types.h>
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

public void
create_terel_armour()
{
    set_armour_size(LARGE);

    set_name("boots");
    set_pname("pairs of boots");
    set_short("pair of thick hide boots");
    set_pshort("pairs of thick hide boots");
    set_long("A pair of thick hide boots.\n");
    set_adj("thick");
    add_adj("hide");
    add_name("armour");
    add_pname("armours");

    set_default_armour(25, A_FEET, 0, 0);
}
