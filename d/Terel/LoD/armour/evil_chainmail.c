




/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * evil_chainmail.c
 *
 * worn by evil guards in LoD.
 *
 * a evil chainmail Redhawk 921108
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
    set_short("darkened chainmail");
    set_long("It's a chainmail made of steel that radiates evil.\n");
    set_adj(({"evil"}));

    set_default_armour(20, A_BODY, 0, 0);
    set_am(({3, 2, 3}));
    set_am(({4,-2,-2}));
}
