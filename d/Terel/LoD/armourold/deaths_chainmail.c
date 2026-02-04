/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * deaths_chainmail.c
 *
 * work by deaths knights and master knights in LoD
 *
 * a "deadly" chainmail Redhawk 920924
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
    set_short("death's chainmail");
    set_long("It is a darkened chainmail that looks like it belongs to " +
	     "Death himself.\n");
    set_adj(({"death's"}));
    add_adj("deaths");

    set_default_armour(39, A_BODY, 0, 0);
    set_am(({ 5, -2, -3}));
}
