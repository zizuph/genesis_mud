
/* Orc arrows for the Uruk-hai in Moria
 * Based on the haradrim arrows from Gondor.
 * Thanks Rohim and Gondor!!
 * Finwe, June 2004
 */

#include "/d/Shire/sys/defs.h"  
#include </stdproperties.h>

inherit "/lib/keep";
inherit "/std/arrow";

public void
create_arrow()
{
    FIXEUID;
    set_adj(({"long", "heavy"}));
    set_keep();
    
    set_projectile_id("shire_moria_long_arrow");
    set_hit(40);
    set_pen(46);
}

string
get_projectile_long(string str, object for_obj, int num)
{
    if (num == 1)
    {
	return "This is a long, heavy arrow used by orc longbows. The shaft " +
        "is made of wood and dyed black and the fins are made from " +
        "black feathers. The tip has been hammered from a piece of " +
        "iron and ground to a sharp edge.\n";

    }
    else
    {
	return "These are long, heavy arrows used by orc longbows. The " +
        "shafts are made of wood and dyed black and the fins are made " +
        "from black feathers. Each tip has been hammered from a piece " +
        "of iron and ground to a sharp edge.\n";
    }
}

