/*
 *  An enchanted diamond that can be inserted in to masterwork
 *  armours to improve the armour AC.
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
    config_gems("diamond", "diamonds", "teardrop-shaped", 6048,
        GEM_EXTREMELY_RARE, 1, 2);
    add_name("_iron_ward_diamond");
    set_random_placement(0);
    add_adj("teardrop");
    add_adj("shaped");
    set_long("@@default_gem_long@@ Diamond is a rare, "+
        "brilliant gem of incredible hardness and durability. " +
        "This dun and ecru diamond has formed in to the shape " +
        "of a teardrop.\n");

    add_prop(MAGIC_AM_ID_INFO, ({ "This teardrop-shaped diamond " +
        "is enchanted with an Iron Ward, and when inserted in to " +
        "armour specifically designed by a master smith it will " +
        "provide additional protection to the wearer.\n", 25 }));
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));

    add_prop(OBJ_S_WIZINFO, "This gem can be inserted in to masterwork " +
        "armours crafted by Theros Ironfeld in Solace, Krynn. When " +
        "inserted, the armour value increases the AC by 2. The armour " +
        "can be found at " +
        "/d/Krynn/common/warfare/rewards/masterwork_warfare_armour.c \n");
}


