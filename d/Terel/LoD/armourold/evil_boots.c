/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * evil_boots.c
 *
 * worn by evil guards in LoD.
 *
 * a pair of evil boots Redhawk 921108
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
    set_pname("pairs of boots");
    set_short("pair of darkened boots");
    set_pshort("pairs of darkened boots");
    set_long("Its a pair of darkned boots.\n");
    set_adj(({"darkned"}));
    add_name("armour");
    add_pname("armours");

    set_default_armour(10, A_FEET, 0, 0);
}
