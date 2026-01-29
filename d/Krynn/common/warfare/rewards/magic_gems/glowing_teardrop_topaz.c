/*
 *  An enchanted blue topaz that can be inserted in to masterwork
 *  armours to improve the wearer's resistance to water.
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
    config_gems("topaz", "topazes", "glowing teardrop-shaped blue", 1432, 
        GEM_EXTREMELY_RARE, 6, 10);
    add_name("_greater_water_resistance_crystal");
    set_random_placement(0);
    add_adj("teardrop");
    add_adj("shaped");
    add_adj("blue");
    set_long("@@default_gem_long@@  The topaz is a hard, "+
        "brilliant stone that throbs with a gentle yet vibrant blue " +
        "light. It has been cut into the shape of a teardrop.\n");

    add_prop(OBJ_I_LIGHT, LIGHT_PASSIVE);
    add_prop(MAGIC_AM_ID_INFO, ({ "This teardrop-shaped blue topaz " +
        "is enchanted with a Greater Water Ward, and when inserted in to " +
        "armour specifically designed by a master smith it will " +
        "provide additional protection to the wearer from water " +
        "magic.\n", 25 }));
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));

    add_prop(OBJ_S_WIZINFO, "This gem can be inserted in to masterwork " +
        "armours crafted by Theros Ironfeld in Solace, Krynn. When " +
        "inserted, the water resistances of the wearer increases by 6. " +
        "The armour can be found at " +
        "/d/Krynn/common/warfare/rewards/masterwork_warfare_armour.c \n");
}


