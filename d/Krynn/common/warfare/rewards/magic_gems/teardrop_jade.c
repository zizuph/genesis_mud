/*
 *  An enchanted jade that can be inserted in to masterwork
 *  armours to improve the wearer's resistance to poison
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
    config_gems("jade", "jades", "teardrop-shaped green", 1576, 
        GEM_EXTREMELY_RARE, 40, 62);

    add_name("_poison_resistance_crystal");
    set_random_placement(0);
    add_adj("teardrop");
    add_adj("shaped");
    add_adj("green");
    set_long("@@default_gem_long@@ Jade is normally "+
        "fairly soft and yet quite durable, making it "+
        "useful in the carving of figurines and jewelry. "+
        "This jade gemstone is a hard, virulent shade of green " +
        "carved into the shape of a teardrop.\n");

    add_prop(OBJ_I_LIGHT, LIGHT_PASSIVE);
    add_prop(MAGIC_AM_ID_INFO, ({ "This teardrop-shaped green jade " +
        "is enchanted with a Poison Ward, and when inserted in to " +
        "armour specifically designed by a master smith it will " +
        "provide protection to the wearer from poison " +
        "magic.\n", 25 }));
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));

    add_prop(OBJ_S_WIZINFO, "This gem can be inserted in to masterwork " +
        "armours crafted by Theros Ironfeld in Solace, Krynn. When " +
        "inserted, the poison resistances of the wearer increases by 3. " +
        "The armour can be found at " +
        "/d/Krynn/common/warfare/rewards/masterwork_warfare_armour.c \n");
}


