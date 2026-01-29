/*
 *  An enchanted gem that can be inserted in to masterwork
 *  armours to improve the hunting skill.
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
    config_gems("aragonite", "aragonites", "oval-shaped amber", 72, 
        GEM_SLIGHTLY_COMMON, 1, 2);

    add_name("_crystal_of_hunting");
    add_adj("oval");
    add_adj("shaped");
    add_adj("oval-shaped");
    add_adj("amber");
    set_short("oval-shaped amber aragonite");
    set_long("@@default_gem_long@@ This gemstone is naturally "+
        "found in stalactites or around natural hot springs, and "+
        "is often referred to as 'iron flowers' due to their " +
        "thin, branch-like crystal formations.\n");

    set_random_placement(0);

    add_prop(MAGIC_AM_ID_INFO, ({ "This oval-shaped amber aragonite " +
        "is an enchanted Crystal of Hunting, and when inserted in to " +
        "armour specifically designed by a master smith it will enhance " +
        "the hunting skill of the wearer.\n", 25 }));
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));
    add_prop(OBJ_S_WIZINFO, "This gem can be inserted in to masterwork " +
        "armours crafted by Theros Ironfeld in Solace, Krynn. When " +
        "inserted, the wearer's hunting skill increases by 5. The armour " +
        "can be found at " +
        "/d/Krynn/common/warfare/rewards/masterwork_warfare_armour.c \n");
}


