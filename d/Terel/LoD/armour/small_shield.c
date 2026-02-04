




/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * small_helmet.c
 *
 * worn by small guards is LoD.
 *
 * a small shield Redhawk 920728
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
    set_name(({"shield"}));
    set_pname("shields");
    set_short("small shield");
    set_pshort("small shields");
    set_long("Its a small elf made shield of good quality.\n");
    set_adj(({"small"}));
    add_adj("metal");  /* added by Gorboth, July 2007 */

    set_default_armour(10, A_SHIELD, 0, 0);
}
