/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * battle_helmet.c
 *
 * worn by captains, lietenants in LoD.
 *
 * a battle legion helmet Redhawk 921111
 * Modified by Sorgum 941026
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
    set_name("helmet");
    set_short("battle helmet");
    set_long("A battle helmet that is standard issue for soldiers in the" +
	     " legion of darkness.\n");
    set_adj(({"battle"}));

    set_default_armour(34, A_HEAD, 0, 0);
    set_am(({ 4, 2, -6}));
}
