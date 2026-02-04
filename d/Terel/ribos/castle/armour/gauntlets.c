
/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * gauntlets.c
 *
 * worn by the better knights in Ribos
 *
 */

#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

#include <wa_types.h>

public void
create_terel_armour()
{
    set_name(({"gauntlets", "gloves"}));
    set_adj(({"steel", "gleaming", "fine"}));
    set_short("fine steel gauntlets");
    set_long("These are a prime example of the craftsmanship of the Ribos " +
             "smiths.  This is a gleaming set of steel gauntlets, worn " +
             "by only the best Ribos Knights.\n");
    set_ac(33);
    set_at(A_HANDS);
    set_am(({0,0,0}));
}

