/*
 *  An enchanted yellow amber that can be inserted in to masterwork
 *  armours to grant a dark vision.
 *
 *  Arman Kharas, November 2018
 */

inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"
#include "/d/Krynn/common/defs.h"
#include <macros.h>

void
create_gems()
{
    config_gems("amber", "ambers", "triangular-shaped yellow", 1432, 
        GEM_EXTREMELY_RARE, 6, 10);
    add_name("_see_dark_crystal");
    set_random_placement(0);
    add_adj("triangular");
    add_adj("shaped");
    add_adj("yellow");
    set_long("@@default_gem_long@@ This piece of amber is " +
        "fossilized tree sap, with a curious piece of " +
        "star-metal captured within that looks like a cat's " +
        "eye. The amber has been cut into a triangular shape.\n");

    add_prop(MAGIC_AM_ID_INFO, ({ "This triangular-shaped yellow amber " +
        "is enchanted with a Night's Eye charm. When inserted in to " +
        "armour specifically designed by a master smith it will " +
        "provide night vision to the wearer when activated " +
        "by pressing the gemstone.\n", 25 }));
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));

    add_prop(OBJ_S_WIZINFO, "This gem can be inserted in to masterwork " +
        "armours crafted by Theros Ironfeld in Solace, Krynn. When " +
        "inserted and activated, the wearer gains one level of " +
        "darkvision. The armour can be found at " +
        "/d/Krynn/common/warfare/rewards/ \n");
}


