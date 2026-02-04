
/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * evil_boots.c
 *
 * worn by evil guards in LoD.
 *
 * a pair of evil boots Redhawk 921108
 * Modified by Sorgum 941026
 *
 * Updated to reflect use of new standard armour in Terel.
 * Torm, Sept 98
 * Lilith Dec 2021: believe it or not there were 2 typso in the long desc ;)
 */

#include <wa_types.h>
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

public void
create_terel_armour()
{
    set_name(({"boots", "pair of boots"}));
    set_pname("pairs of boots");
    set_short("pair of darkened boots");
    set_pshort("pairs of darkened boots");
    set_long("It's a pair of darkened boots.\n");
    set_adj(({"darkned"}));
    add_name("armour");
    add_pname("armours");

    set_default_armour(10, A_FEET, 0, 0);
}
