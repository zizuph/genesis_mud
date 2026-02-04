/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * boots.c
 *
 * worn by the better knights in Ribos
 *
 * Vader
 * Modified by Sorgum 950602
 * Modified by Bronco 950719
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
    add_adj("fine");
    set_short("fine silver boots");
    set_long("These boots, worn by the better Ribos Knights, are made " +
	     "from finely polished silver.  There is a black band running" +
	     "around the top of the boots.\n");
    set_ac(32);
    set_at(A_FEET);
    set_am(({0, 0, 0}));
}
