/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * hat.c
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
    set_name("hat");
    set_adj("silver");
    set_short("silver cloth hat");
    set_long("This hat is one of the few items a Knight of Ribos " +
	     "would wear that\ndoesn't actually have silver in it.\n");
    set_ac(4);
    set_at(A_HEAD);
    set_am(({0, 0, 0}));
}
