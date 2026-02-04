/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * dark_helmet.c
 *
 * worn by darkness_knights and dark guards in LoD
 *
 * dark legion helmet Redhawk 920812
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
    set_short("dark helmet");
    set_long("A darkened helmet that is a bit better than standard in " +
	     "the legion of darkness.\n");
    set_adj(({"dark"}));

    set_default_armour(25, A_HEAD, 0, 0);
    set_am(({4, 2, -6}));
}
