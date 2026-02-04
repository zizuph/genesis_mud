/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * small_helmet.c
 *
 * worn by small guards and the war officer is LoD.
 *
 * a small helmet Redhawk 920728
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
    set_short("small helmet");
    set_long("A small elf made helmet of good quality.\n");
    set_adj(({"small"}));

    set_default_armour(15, A_HEAD, 0, 0);
    set_am(({4, 2, -6}));
}
