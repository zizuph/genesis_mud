
/* Elvish arrows made in Rivendell
 * Finwe, June 2004
 *
 *  Modification log:
 *     
 *     2006.09.05, Toby:
 *       Added set_short to solve the 'A broken broken arrow.' bug
 */

#include "/d/Shire/sys/defs.h"  
#include </stdproperties.h>

inherit "/lib/keep";
inherit "/std/arrow";

public void
create_arrow()
{
    FIXEUID;
    set_adj(({"long", "wooden", "sleek"}));

    set_short("long sleek wooden arrow");
    set_pshort("long sleek wooden arrows");

    set_keep();
    
    set_projectile_id("shire_riv_wood_arrow");
    set_hit(40);
    set_pen(40);
    add_prop(OBJ_I_VALUE,60);   
}

string
get_projectile_long(string str, object for_obj, int num)
{
    if (num == 1)
    {
	return "This is a long, sleek arrow made by elves of Imladris. The " +
        "shaft is made from smooth wood and the fins are made from soft goose " +
        "feathers. The tip has been hammered from a piece of steel and " +
        "ground to a sharp edge.\n";

    }
    else
    {
	return "These are long, sleek arrows made by the elves of Imladris. " +
        "The shafts are made from smooth wood and the fins are made from " +
        "soft goose feathers. Each tip has been hammered from a piece " +
        "of steel and ground to a sharp edge.\n";
    }
}

