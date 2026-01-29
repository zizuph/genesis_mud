/*
 *  An enchanted bloodstone that can be inserted in to masterwork
 *  armours to improve the wearer's resistance to death magic.
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
    config_gems("bloodstone", "bloodstones", "glowing teardrop-shaped", 1432, 
        GEM_EXTREMELY_RARE, 30, 44);

    add_name("_greater_death_resistance_crystal");
    set_random_placement(0);
    add_adj("teardrop");
    add_adj("shaped");
    add_adj("glowing");
    set_long("@@default_gem_long@@ Bloodstone is a green "+
        "variety of chalcedony spotted with tear-shaped "+
        "drops of red jasper. The depth and lustre of the "+
        "stone makes it appear that dark glowing blood is welling up "+
        "from within. It has been cut into the shape of a teardrop.\n");

    add_prop(OBJ_I_LIGHT, LIGHT_PASSIVE);
    add_prop(MAGIC_AM_ID_INFO, ({ "This teardrop-shaped bloodstone " +
        "is enchanted with a Greater Death Ward, and when inserted in to " +
        "armour specifically designed by a master smith it will " +
        "provide protection to the wearer from death " +
        "magic.\n", 25 }));
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));

    add_prop(OBJ_S_WIZINFO, "This gem can be inserted in to masterwork " +
        "armours crafted by Theros Ironfeld in Solace, Krynn. When " +
        "inserted, the death resistances of the wearer increases by 6. " +
        "The armour can be found at " +
        "/d/Krynn/common/warfare/rewards/masterwork_warfare_armour.c \n");
}


