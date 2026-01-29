/*
 *  An enchanted spinel that can be inserted in to masterwork
 *  armours to improve the wearer's resistance to air magic.
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
    config_gems("spinel", "spinels", "glowing teardrop-shaped blue", 1369, 
        GEM_EXTREMELY_RARE, 4, 7);

    add_name("_greater_air_resistance_crystal");
    set_random_placement(0);
    add_adj("teardrop");
    add_adj("shaped");
    add_adj("glowing");
    set_long("@@default_gem_long@@ This spinel is a hard, "+
        "brilliant stone of blue. It glows with an inner light like a " +
        "clear sky, and has been cut into the shape of a teardrop.\n");

    add_prop(OBJ_I_LIGHT, LIGHT_PASSIVE);
    add_prop(MAGIC_AM_ID_INFO, ({ "This teardrop-shaped blue spinel " +
        "is enchanted with a Greater Air Ward, and when inserted in to " +
        "armour specifically designed by a master smith it will " +
        "provide substantial protection to the wearer from air " +
        "magic.\n", 25 }));
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));

    add_prop(OBJ_S_WIZINFO, "This gem can be inserted in to masterwork " +
        "armours crafted by Theros Ironfeld in Solace, Krynn. When " +
        "inserted, the air resistances of the wearer increases by 6. " +
        "The armour can be found at " +
        "/d/Krynn/common/warfare/rewards/masterwork_warfare_armour.c \n");
}


