/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * l_boots.c
 *
 * a pair of leather boots
 *
 * Goldberry January, 2000
 */

#include <wa_types.h>
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

public void
create_terel_armour()
{
    set_name("boots");
    set_pname("pairs of boots");
    set_short("pair of leather boots");
    set_pshort("pairs of leather boots");
    set_long("A pair of supple leather boots.\n");
    set_adj("leather");
    add_name("armour");
    add_pname("armours");

    set_default_armour(15, A_FEET, 0, 0);
}
