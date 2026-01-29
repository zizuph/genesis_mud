/*
 *  An enchanted sea agate that can be inserted in to masterwork
 *  armours to grant the ability to breathe water.
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
    config_gems("agate", "agates", "triangular-shaped blue", 1369, 
        GEM_EXTREMELY_RARE, 6, 13);
    add_name("_watermere_crystal");
    set_random_placement(0);
    add_adj("triangular");
    add_adj("shaped");
    add_adj("blue");
    set_long("@@default_gem_long@@ This rare agate "+
        "swirls with the colours of the sea: blue-green, grey, "+
        "and violet.  This stone is mostly translucent, with "+ 
        "opaque white inclusions that look like the foamy "+
        "crests of waves. It has been cut into " +
        "a triangular shape.\n");

    add_prop(MAGIC_AM_ID_INFO, ({ "This triangular-shaped blue agate " +
        "is an enchanted Watermere Crystal, crafted by the Dargonesti " +
        "sea elves of the Courrain Ocean. When inserted in to " +
        "armour specifically designed by a master smith it will " +
        "provide the wearer the ability to breathe water when activated " +
        "by pressing the gemstone.\n", 25 }));
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));

    add_prop(OBJ_S_WIZINFO, "This gem can be inserted in to masterwork " +
        "armours crafted by Theros Ironfeld in Solace, Krynn. When " +
        "inserted and activated, the wearer gains the breath water " +
        "prop. The armour can be found at " +
        "/d/Krynn/common/warfare/rewards/ \n");
}


