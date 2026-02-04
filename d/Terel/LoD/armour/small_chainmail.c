




/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * deaths_shield.c
 *
 * worn by small guards in LoD.
 *
 * a small chainmail Redhawk 920728
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
    set_short("small chainmail");
    set_long("It is a small elf made chainmail of decent quality.\n");
    set_adj(({"small"}));
    add_adj("metal");  /* added by Gorboth, July 2007 */

    set_default_armour(10, A_BODY, 0, 0);
    set_am(({ -2, 0, 2}));
}
