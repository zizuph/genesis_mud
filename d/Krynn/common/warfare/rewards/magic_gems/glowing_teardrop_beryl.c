/*
 *  An enchanted beryl that can be inserted in to masterwork
 *  armours to improve the wearer's resistance to cold.
 *
 *  Arman Kharas, October 2018
 */

inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"
#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <const.h>

void
create_gems()
{

    config_gems("beryl", "beryls", "glowing teardrop-shaped", 800, 
        GEM_EXTREMELY_RARE, 3, 5);
    add_name("_greater_cold_resistance_crystal");
    set_random_placement(0);
    add_adj("teardrop");
    add_adj("shaped");
    add_adj("colourless");
    set_long("@@default_gem_long@@ Beryl is a lustrous, "+
        "transparent family of gemstones, including emerald "+
        "and aquamarine. This gemstone is pure and colourless, " + 
        "shaped like a teardrop, and radiates an icy cold glow.\n");

    add_prop(OBJ_I_LIGHT, LIGHT_PASSIVE);
    add_prop(MAGIC_AM_ID_INFO, ({ "This teardrop-shaped beryl " +
        "is enchanted with a Greater Cold Ward, and when inserted in to " +
        "armour specifically designed by a master smith it will " +
        "provide additional protection to the wearer from cold " +
        "magic. This magical gemstone has the added effect when in " +
        "close proximity to the mythical Ice Reaver weapon to stop " +
        "it from melting outside of the frigid conditions of the " +
        "Icewall Glacier.\n", 25 }));
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));

    add_prop(OBJ_S_WIZINFO, "This gem can be inserted in to masterwork " +
        "armours crafted by Theros Ironfeld in Solace, Krynn. When " +
        "inserted, the cold resistances of the wearer increases by 6. " +
        "The armour can be found at " +
        "/d/Krynn/common/warfare/rewards/masterwork_warfare_armour.c \n");
}


