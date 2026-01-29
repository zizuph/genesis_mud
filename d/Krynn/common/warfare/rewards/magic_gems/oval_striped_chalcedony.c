/*
 *  An enchanted quartz that can be inserted in to masterwork
 *  armours to improve the enchantment skill.
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
    config_gems("chalcedony", "chalcedonies", "oval-shaped striped", 144, 
        GEM_EXTREMELY_RARE, 40, 67);

    add_name("_crystal_of_enchantment");
    set_random_placement(0);
    add_adj("oval");
    add_adj("shaped");
    add_adj("oval-shaped");
    add_adj("striped");
    set_short("oval-shaped striped chalcedony");
    set_long("@@default_gem_long@@  This chalcedony is a "+
        "variety of banded quartz. It is opaque and "+
        "banded with a variety of colours that create a "+
        "beautifully surreal landscape for the eye.\n");

    add_prop(MAGIC_AM_ID_INFO, ({ "This oval-shaped striped chalcedony " +
        "is an enchanted Crystal of Enchantment, and when inserted in to " +
        "armour specifically designed by a master smith it will enhance " +
        "the enchantment form skill of the wearer.\n", 25 }));
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));
    add_prop(OBJ_S_WIZINFO, "This gem can be inserted in to masterwork " +
        "armours crafted by Theros Ironfeld in Solace, Krynn. When " +
        "inserted, the wearer's enchantment skill increases by 5. The armour " +
        "can be found at " +
        "/d/Krynn/common/warfare/rewards/masterwork_warfare_armour.c \n");
}


