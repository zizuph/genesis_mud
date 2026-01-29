/* Ashlar, 20 Oct 97 */

inherit "/std/armour";
inherit "/lib/keep";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("mail");
    add_name("chainmail");
    add_name("shirt");
    set_adj("chain");
    add_adj("chainmail");
    add_adj("blackened");
    add_adj("black");
    set_short("blackened chainmail shirt");
    set_ac(31);
    set_at(A_TORSO);
    set_long("The " + short() + " is crafted of the finest steel, " +
    "blackened, and decorated with a silver slash running across " +
    "the chest from the left shoulder to the right side of the waist. " +
    "The inside of the shirt is padded with cloth.\n");

    add_prop(OBJ_I_VOLUME, 2150);
}

