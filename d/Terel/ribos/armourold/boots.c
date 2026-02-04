/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * boots.c
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
    set_name("boots");
    set_adj("silver");
    set_short("shiny silver boots");
    set_pshort("pairs of shiny silver boots");
    set_long("These boots, made of polished silver, are used by the " +
	     "Ribos Knights.\n");
    set_ac(30);
    set_at(A_FEET);
    set_am(({0, 0, 0}));
}
