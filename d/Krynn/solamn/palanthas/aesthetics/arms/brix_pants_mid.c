/* 
 * Pants of mid level Brix gang members off Jems Court in
 * Aesthetics quarter of Palanthas.
 *
 * Mortis 05.2006
 *
 */

inherit "/std/armour";
inherit "/lib/keep";

#include <macros.h>
#include <wa_types.h>
#include "../../local.h"

void
create_armour()
{
	set_name("pants");
	set_adj("worn");
	add_adj(({"rough-padded"}));
	set_short("pair of worn rough-padded pants");
	set_pshort("pairs of worn rough-padded pants");
	set_long("Hemp patches keep the worn linen of these shoddy, rough-padded "
	+ "pants together.  They are in poor shape despite being reinforced with "
	+ "quilted pads for additional protection.\n");

	set_ac(14);
	set_am(({-1, -1, 2}));
	set_at(A_LEGS);
	set_condition(1);
}

string
arm_condition_desc()
{
    string str;

    if (query_prop(OBJ_I_BROKEN))
        return "It has been shredded to pieces.\n";

    switch(condition - repair)
    {
        case 0:
            str = "is in pristine condition";
            break;
        case 1:
        case 2:
            str = "is a little disheveled";
            break;
        case 3:
        case 4:
            str = "has ripped in a few places";
            break;
        case 5:
        case 6:
        case 7:
            str = "is torn up badly";
            break;
        default:
            str = "has almost been torn to shreds";
            break;
    }

    return "It looks like it " + str + ".\n";
}
