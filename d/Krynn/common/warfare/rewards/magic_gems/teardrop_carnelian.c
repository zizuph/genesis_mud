/*
 *  An enchanted carnelian that can be inserted in to masterwork
 *  armours to improve the wearer's resistance to fire.
 *
 *  Arman Kharas, October 2018
 */

inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"
#include "/d/Krynn/common/defs.h"
#include <macros.h>

void
create_gems()
{
    config_gems("carnelian", "carnelians", "teardrop-shaped", 288, 
        GEM_EXTREMELY_RARE, 26, 38);
    add_name("_fire_resistance_crystal");
    set_random_placement(0);
    add_adj("teardrop");
    add_adj("shaped");
    set_long("@@default_gem_long@@ This Carnelian is a bright "+
        "red variety of chalcedony, with swirls of orange " +
        "quartz that seem to dance like fire. It has been cut " +
        "into the shape of a teardrop.\n");

    add_prop(MAGIC_AM_ID_INFO, ({ "This teardrop-shaped carnelian " +
        "is enchanted with a Flame Ward, and when inserted in to " +
        "armour specifically designed by a master smith it will " +
        "provide additional protection to the wearer from fire.\n", 25 }));
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));

    add_prop(OBJ_S_WIZINFO, "This gem can be inserted in to masterwork " +
        "armours crafted by Theros Ironfeld in Solace, Krynn. When " +
        "inserted, the fire resistances of the wearer increases by 3. " +
        "The armour can be found at " +
        "/d/Krynn/common/warfare/rewards/masterwork_warfare_armour.c \n");
}


