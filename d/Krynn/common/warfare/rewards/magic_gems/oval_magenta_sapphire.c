/*
 *  An enchanted sapphire that can be inserted in to masterwork
 *  armours to improve the disarm trap skill.
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
    config_gems("sapphire", "sapphires", "oval-shaped magenta", 2345, 
        GEM_EXTREMELY_RARE, 2, 4);

    add_name("_crystal_of_disarming");
    set_random_placement(0);
    add_adj("oval");
    add_adj("shaped");
    add_adj("oval-shaped");
    add_adj("magenta");
    set_short("oval-shaped magenta sapphire");
    set_long("@@default_gem_long@@ Sapphire is a gem "+
        "of great value, brilliance, and durability. This "+
        "sapphire seems to be a purplish red colour, " +
        "and has been carved into an oval shape.\n");

    add_prop(MAGIC_AM_ID_INFO, ({ "This oval-shaped mauve sapphire " +
        "is an enchanted Crystal of Disarming, and when inserted in to " +
        "armour specifically designed by a master smith it will enhance " +
        "the find and remove traps skill of the wearer.\n", 25 }));
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));
    add_prop(OBJ_S_WIZINFO, "This gem can be inserted in to masterwork " +
        "armours crafted by Theros Ironfeld in Solace, Krynn. When " +
        "inserted, the wearer's disarm traps skill increases by 5. The " +
        "armour can be found at " +
        "/d/Krynn/common/warfare/rewards/masterwork_warfare_armour.c \n");
}


