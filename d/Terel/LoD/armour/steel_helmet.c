




/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * steel_helmet.c
 *
 * worn by sergeants and stell guards in LoD.
 *
 * a steel helmet Redhawk 920812
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
    set_name("helmet");
    set_short("steel helmet");
    set_long("A steel helmet of good quality.\n");
    set_adj(({"steel"}));

    set_default_armour(25, A_HEAD, 0, 0);
    set_am(({4, 2, -6}));
}
