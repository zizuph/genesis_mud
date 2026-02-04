




/* This comment tells emacs to use c++-mode  -*- C++ -*- */
/*
 * robe.c
 *
 * Sawoq's robe.
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
    set_name("robe");
    set_long("It's a white robe of high quality.\n");
    set_adj("white");
    set_default_armour(24, A_ROBE, 0, 0);
    set_am(({ 2, 2, -4}));

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 600);
}
