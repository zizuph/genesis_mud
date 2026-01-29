/*
 *  An enchanted yellow topaz that can be inserted in to masterwork
 *  armours to grant a protection from divination ability.
 *
 *  Arman Kharas, October 2018
 */

inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"
#include "/d/Krynn/common/defs.h"
#include <macros.h>

void
create_gems()
{
    config_gems("topaz", "topazes", "triangular-shaped yellow", 1432, 
        GEM_EXTREMELY_RARE, 6, 10);
    add_name("_scry_protection_crystal");
    set_random_placement(0);
    add_adj("triangular");
    add_adj("shaped");
    add_adj("yellow");
    set_long("@@default_gem_long@@ The topaz is a hard, "+
        "brilliant stone of a wonderfully clear yellow " +
        "colour. is very rare and expensive, and should "+
        "not be confused with the yellow quartz known as " +
        "citrine. It has been cut into a triangular shape.\n");

    add_prop(MAGIC_AM_ID_INFO, ({ "This triangular-shaped yellow topaz " +
        "is enchanted with a Scry Ward, and when inserted in to " +
        "armour specifically designed by a master smith it will " +
        "provide protection to the wearer from scrying when activated " +
        "by pressing the gemstone.\n", 25 }));
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));

    add_prop(OBJ_S_WIZINFO, "This gem can be inserted in to masterwork " +
        "armours crafted by Theros Ironfeld in Solace, Krynn. When " +
        "inserted and activated, the wearer gains scry resistance prop " +
        "with an effectiveness of 95% chance of blocking a scry. " +
        "The armour can be found at " +
        "/d/Krynn/common/warfare/rewards/masterwork_warfare_armour.c \n");
}


