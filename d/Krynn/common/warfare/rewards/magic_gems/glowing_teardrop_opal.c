/*
 *  An enchanted opal that can be inserted in to masterwork
 *  armours to improve the wearer's resistance to life magic.
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
    config_gems("opal", "opals", "glowing teardrop-shaped", 864, 
        GEM_EXTREMELY_RARE, 3, 5);

    add_name("_greater_life_resistance_crystal");
    set_random_placement(0);
    add_adj("teardrop");
    add_adj("shaped");
    add_adj("glowing");
    set_long("@@default_gem_long@@ There are few gemstones "+
        "to rival the opal for beauty and variety in appearance "+
        "and colour. There are no two stones alike, though the "+
        "most outstanding characteristic of this unique gem is "+
        "the unusual, intense display of colours flashing out "+
        "like mini-rainbows in even the poorest light.\n");

    add_prop(OBJ_I_LIGHT, LIGHT_PASSIVE);
    add_prop(MAGIC_AM_ID_INFO, ({ "This teardrop-shaped opal " +
        "is enchanted with a Greater Life Ward, and when inserted in to " +
        "armour specifically designed by a master smith it will " +
        "provide substantial protection to the wearer from life " +
        "magic.\n", 25 }));
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));

    add_prop(OBJ_S_WIZINFO, "This gem can be inserted in to masterwork " +
        "armours crafted by Theros Ironfeld in Solace, Krynn. When " +
        "inserted, the life resistances of the wearer increases by 6. " +
        "The armour can be found at " +
        "/d/Krynn/common/warfare/rewards/masterwork_warfare_armour.c \n");
}


