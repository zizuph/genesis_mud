




/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * deaths_shield.c
 *
 * worn by deaths knights and master knights in LoD.
 *
 * a "deadly shield Redhawk 920924
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
    set_short("death's shield");
    add_adj("metal");  /* it is, isn't it? -Gorboth */
    set_long("It's a darkened shield that looks like it belongs to " +
	     "Death himself.\n");
    set_adj(({"death's"}));
    add_adj("deaths");

    set_default_armour(35, A_SHIELD, 0, 0);
}
