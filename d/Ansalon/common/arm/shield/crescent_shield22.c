/* Ashlar, 20 Oct 97 */

inherit "/std/armour";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("shield");
    add_name("buckler");
    set_adj("black");
    add_adj("crescent-marked");
    add_adj("crescent");
    add_adj("marked");
    set_short("black crescent-marked shield");
    
    set_ac(22);
    set_at(A_SHIELD);
    set_long("The " + short() + " is a round shield made of metal. " +
	"It is painted black and the face is covered by a crescent-shaped " +
	"indentation.\n");

    add_prop(OBJ_I_VOLUME, 2200);
}

