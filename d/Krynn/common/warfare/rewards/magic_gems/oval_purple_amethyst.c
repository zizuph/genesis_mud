/*
 *  An enchanted quartz that can be inserted in to masterwork
 *  armours to improve the conjuration skill.
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
    config_gems("amethyst", "amethysts", "oval-shaped purple", 428, 
        GEM_EXTREMELY_RARE, 3, 5);

    add_name("_crystal_of_conjuration");
    set_random_placement(0);
    add_adj("oval");
    add_adj("shaped");
    add_adj("oval-shaped");
    add_adj("purple");
    set_short("oval-shaped purple amethyst");
    set_long("@@default_gem_long@@ Amethyst is a trans"+
        "parent purple variety of quartz. This gemstone is "+
        "relatively hard, and radiates brilliantly in the light - " +
        "you would say unnaturally so.\n");

    add_prop(MAGIC_AM_ID_INFO, ({ "This oval-shaped purple amethyst " +
        "is an enchanted Crystal of Conjuration, and when inserted in to " +
        "armour specifically designed by a master smith it will enhance " +
        "the conjuration form skill of the wearer.\n", 25 }));
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));
    add_prop(OBJ_S_WIZINFO, "This gem can be inserted in to masterwork " +
        "armours crafted by Theros Ironfeld in Solace, Krynn. When " +
        "inserted, the wearer's conjuration skill increases by 5. The armour " +
        "can be found at " +
        "/d/Krynn/common/warfare/rewards/masterwork_warfare_armour.c \n");
}


