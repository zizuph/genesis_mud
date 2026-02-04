/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * h_g_armour.c
 *
 * Vader
 * Modified by Sorgum 950602
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
    ::create_armour();
    set_name(({"plate", "platemail", "armour", "armor"}));
    set_adj("silver");
    set_short("shiny silver platemail");
    set_long("This not only can protect you from an opponents blows, but can "
	     + "blind him in bright sunlight.\n");
    set_ac(25);
    set_at(A_BODY);
    set_am(({0,0,0}));
}
