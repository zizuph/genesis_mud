




/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * iron_chainmail.c
 *
 * worn by iron guards in LoD.
 *
 * a evil chainmail Redhawk 921108
 * Modified by Sorgum 941026
 *
 * Updated to reflect use of new standard armour in Terel.
 * Torm, Sept 98
 */

#include <wa_types.h>
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

public void
create_terel_armour()
{
    set_name("chainmail");
    set_short("iron chainmail");
    set_long("Its a iron chainmail that the some of the soldiers in " +
	     "the legion use.\n");
    set_adj(({"iron"}));

    set_default_armour(20, A_BODY, 0, 0);
    set_am(({4,-2,-2}));
}
