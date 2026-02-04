/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * deaths_shield.c
 *
 * worn by small guards in LoD.
 *
 * a small chainmail Redhawk 920728
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
    set_name("chainmail");
    set_short("small chainmail");
    set_long("It is a small elf made chainmail of decent quality.\n");
    set_adj(({"small"}));

    set_default_armour(10, A_BODY, 0, 0);
    set_am(({ -2, 0, 2}));
}
