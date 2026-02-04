




/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * dark_helmet.c
 *
 * worn by darkness_knights and dark guards in LoD
 *
 * dark legion helmet Redhawk 920812
 * Modified by Sorgum 941026
 *
 * Updated to reflect use of new standard armour in Terel.
 * Torm, Sept 98
 */

#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

#include <wa_types.h>


public void
create_terel_armour()
{
    set_name("helmet");
    set_short("dark helmet");
    set_long("A darkened helmet that is a bit better than standard in " +
	     "the legion of darkness.\n");
    set_adj(({"dark"}));
    add_adj("metal");  /* added by Gorboth, July 2007 */

    set_default_armour(25, A_HEAD, 0, 0);
    set_am(({4, 2, -6}));
}
