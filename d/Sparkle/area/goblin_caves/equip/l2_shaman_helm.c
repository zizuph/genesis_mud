/*
 * Helm for shaman level 2
 * - Boreaulam, August 2014
 */
#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>

inherit L2_SHAMAN_ARMOUR;

/*
 * Function name:        create_armour
 * Description  :        constructor for the object
 */
void
create_armour()
{
	::create_armour();
    set_name("helmet");
    add_name("helm");
    set_short(query_adj() + " helmet");
    set_long("This is an extremely well-made helmet which has been crafted " + 
        "from " + query_adj() + ". The workmanship is quite remarkable, and " + 
        query_long_add() + " directed at your head.\n");
    set_at(A_LEGS);
    set_at(A_HEAD);
} /* create_armour */