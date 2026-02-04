/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * pcollar.c
 *
 * Platinum collar worn by white wolves.
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
    set_name("collar");
    set_adj("platinum");
    set_short("platinum collar");
    set_long("There is an inscription in it:\n"+
	     "Name: Rufus\n"+
	     "Address: The orc caves of Terel.\n"+
	     "If I am lost, feed me live creatures, especially humans.\n");
    set_ac(40);
    set_at(A_NECK);
    set_am(({0, 0, 0}));
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 103);
}
