




/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * dark_chainmail.c
 *
 * worn by darkness_knights and dark guards in LoD
 *
 * a dark legion chainmail redhawk 920812
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
    set_short("dark chainmail");
    set_long("It is a dark chainmail of good quality that is " +
             "normally worn by soldiers in the legion of darkness.\n");
    set_adj(({"dark"}));
    add_adj("metal");  /* added by Gorboth, July 2007 */

    set_default_armour(30, A_BODY, 0, 0);
    set_am(({ 3, -1, -2}));
}
