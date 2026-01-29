/*
 *  An enchanted garnet that can be inserted in to masterwork
 *  armours to grant a quickness boost.
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
    config_gems("garnet", "garnets", "triangular-shaped orange", 1369, 
        GEM_EXTREMELY_RARE, 6, 13);
    add_name("_reflex_crystal");
    set_random_placement(0);
    add_adj("triangular");
    add_adj("shaped");
    add_adj("orange");
    set_long("@@default_gem_long@@ This rare garnet is a hard " +
        "and durable gemstone coloured a brilliant orange " +
        "that blazes with amazing clarity. It has been cut into " +
        "a triangular shape.\n");

    add_prop(MAGIC_AM_ID_INFO, ({ "This triangular-shaped orange garnet " +
        "is an enchanted Reflex Crystal. When inserted in to " +
        "armour specifically designed by a master smith it will " +
        "provide the wearer enhanced reflexes when activated " +
        "by pressing the gemstone.\n", 25 }));
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));

    add_prop(OBJ_S_WIZINFO, "This gem can be inserted in to masterwork " +
        "armours crafted by Theros Ironfeld in Solace, Krynn. When " +
        "inserted and activated, the wearer gains a boost in the " +
        "quickness prop by 15. The armour can be found at " +
        "/d/Krynn/common/warfare/rewards/ \n");
}


