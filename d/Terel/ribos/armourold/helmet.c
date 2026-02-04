/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * helmet.c
 *
 * worn by knights in Ribos
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
    set_name("helmet");
    set_adj("silver");
    set_short("shiny silver helmet");
    set_long("This helmet, which is made of finely polished silver, " +
	     "is but one distinguishing piece worn by all Ribos Knights.\n");
    set_ac(30);
    set_at(A_HEAD);
    set_am(({0, 0, 0}));
}
