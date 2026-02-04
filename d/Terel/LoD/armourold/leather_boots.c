/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * leather_boots.c
 *
 * worn by devils knights and iron guards in LoD.
 * 
 * a pair of leather boots Redhawk 921027
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
    set_name(({"boots", "pair of boots"}));
    add_name("armour");
    add_pname("armours");
    set_pname("pairs of boots");
    set_short("pair of leather boots");
    set_pshort("pairs of leather boots");
    set_long("Its a pair of leather boots that is used in the legion " +
	     "of darkness.\n");
    set_adj(({"leather"}));

    set_default_armour(10, A_FEET, 0, 0);
}
