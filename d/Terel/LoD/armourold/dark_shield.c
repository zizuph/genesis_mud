/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * dark_shield.c
 *
 * worn by darkness knights and dark guards in LoD.
 *
 * dark legion shield Redhawk 920812
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
    set_name(({"shield"}));
    set_pname("shields");
    set_short("dark shield");
    set_pshort("dark shields");
    set_long("Its a dark shield that is standard issue in the legion " +
	     "of darkness.\n");
    set_adj(({"dark"}));
    add_name("armour");
    add_pname("armours");

    set_default_armour(30, A_SHIELD, 0, 0);
}
