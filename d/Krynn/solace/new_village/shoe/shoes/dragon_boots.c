/* 
 * Louie 2005
 * Designed by Anahita
 */

inherit "/std/armour";

#include "/d/Krynn/common/defs.h"
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

public void
create_armour()
{ 
    set_name("boots");
    set_pname("boots");
    add_name("armour");
    add_pname("armours");
    set_adj(({"thigh-high","dragon"}));
    add_adj(({"black","leather"}));
    add_name(({"pair of boots","pair of dragon boots"}));
    add_pname(({"pairs of boots","pairs of dragon boots"}));
    set_short("pair of thigh-high dragon boots");
    set_pshort("pairs of thigh-high dragon boots");
    set_ac(35);
    set_at(A_FEET);
    set_long("These black leather boots "+
        "feature an exquisite design of two dragons locked in aerial "+
        "combat.  The beads, gems, and metallic thread in the design "+
        "catch the light and give an illusion of movement to the "+
        "beasts and their flaming breath.  "+
        "\n");

    add_item(({"beads","beads","gems","thread","metallic thread"}),
        "The various beads, gems, and the metallic thread that are "+
        "used to decorate the boots appear to be of the highest quality.\n");

    add_item(({"design","exquisite design"}),
        "The design of the dragons was obviously crafted by expert hands.\n");

    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(35, A_HEAD));
    //expensive!
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(35) * 2);
}
