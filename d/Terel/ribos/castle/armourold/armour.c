/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * armour.c
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
    set_name(({"mail", "chainmail", "chain mail", "armour", "armor"}));
    set_adj("steel");
    set_short("fine steel chainmail");
    set_long("This is a prime example of the craftsmanship of the Ribos " +
	     "smiths.  It is a gleaming suit of steel chainmail, worn " +
	     "by only the best Ribos Knights.\n");
    set_ac(33);
    set_at(A_BODY);
    set_am(({0,0,0}));
}
