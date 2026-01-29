/*
 *  An enchanted quartz that can be inserted in to masterwork
 *  armours to improve the illusion skill.
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
    config_gems("quartz", "quartzes", "oval-shaped milky", 12, 
        GEM_EXTREMELY_RARE, 66, 88);

    add_name("_crystal_of_illusion");
    set_random_placement(0);
    add_adj("oval");
    add_adj("shaped");
    add_adj("oval-shaped");
    add_adj("milky");
    set_short("oval-shaped milky quartz");
    set_long("@@default_gem_long@@ Quartz, perhaps the most "+
        "common mineral to occur in crystalline form, is also "+
        "beautiful and affordable. This quartz is of a milky white " +
        "colour that seems to swirl like a trapped cloud, dazzling " +
        "the eye.\n");

    add_prop(MAGIC_AM_ID_INFO, ({ "This oval-shaped milky quartz " +
        "is an enchanted Crystal of Illusion, and when inserted in to " +
        "armour specifically designed by a master smith it will enhance " +
        "the illusion form skill of the wearer.\n", 25 }));
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));
    add_prop(OBJ_S_WIZINFO, "This gem can be inserted in to masterwork " +
        "armours crafted by Theros Ironfeld in Solace, Krynn. When " +
        "inserted, the wearer's illusion skill increases by 5. The armour " +
        "can be found at " +
        "/d/Krynn/common/warfare/rewards/masterwork_warfare_armour.c \n");
}


