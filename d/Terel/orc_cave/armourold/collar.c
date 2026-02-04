/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * collar.c
 *
 * Gold collar worn by grey wolves.
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
    set_adj("gold");
    set_short("gold collar");
    set_long("There is an inscription in it:\n"+
	     "Name: Fido\n"+
	     "Address: The orc caves of Terel.\n"+
	     "If I am lost, feed me live elves or hobbits.\n");
    set_ac(30);
    set_at(A_NECK);
    set_am(({0, 0, 0}));
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 103);
}
