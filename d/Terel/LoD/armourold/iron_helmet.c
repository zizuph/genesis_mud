/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * iron_helmet.c
 *
 * worn by iron guards in LoD.
 *
 * a iron helmet Redhawk 921027
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
    set_short("iron helmet");
    set_long("A iron helmet of the legion of darkness.\n");
    set_adj(({"iron"}));

    set_default_armour(20, A_HEAD, 0, 0);
    set_am(({4, 2, -6}));
}
