/*
 *  An enchanted quartz that can be inserted in to masterwork
 *  armours to improve the abjuration skill.
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
    config_gems("agate", "agates", "oval-shaped brown", 72, 
        GEM_EXTREMELY_RARE, 1, 2);

    add_name("_crystal_of_abjuration");
    set_random_placement(0);
    add_adj("oval");
    add_adj("shaped");
    add_adj("oval-shaped");
    add_adj("brown");
    set_short("oval-shaped brown agate");
    set_long("@@default_gem_long@@  This agate is a type of "+
        "brown chalcedony quartz. "+
        "Partially translucent, with opaque white inclusions "+
        "that form ribbons and swirls, it is unusually hard "+
        "and roughly cut.\n");

    add_prop(MAGIC_AM_ID_INFO, ({ "This oval-shaped brown agate " +
        "is an enchanted Crystal of Abjuration, and when inserted in to " +
        "armour specifically designed by a master smith it will enhance " +
        "the abjuration form skill of the wearer.\n", 25 }));
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));
    add_prop(OBJ_S_WIZINFO, "This gem can be inserted in to masterwork " +
        "armours crafted by Theros Ironfeld in Solace, Krynn. When " +
        "inserted, the wearer's abjuration skill increases by 5. The armour " +
        "can be found at " +
        "/d/Krynn/common/warfare/rewards/masterwork_warfare_armour.c \n");
}


