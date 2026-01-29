/*
 *  An enchanted green peridot that can be inserted in to masterwork
 *  armours to grant the ability to see invisible objects.
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
    config_gems("peridot", "peridots", "triangular-shaped green", 1369, 
        GEM_EXTREMELY_RARE, 6, 13);
    add_name("olivine");
    set_random_placement(0);
    add_name("_see_invisible_crystal");
    set_random_placement(0);
    add_adj("triangular");
    add_adj("shaped");
    add_adj("green");
    set_long("@@default_gem_long@@ Peridot is a transparent "+
        "yellowish-green variety of olivine. While not particularly " +
        "brilliant, it is rather easily faceted to display the " +
        "exceptional richness of its colour. It has been cut into " +
        "a triangular shape.\n");

    add_prop(MAGIC_AM_ID_INFO, ({ "This triangular-shaped green peridot " +
        "is an enchanted Revelation Crystal, and when inserted in to " +
        "armour specifically designed by a master smith it will " +
        "provide the wearer the ability to see the invisible when activated " +
        "by pressing the gemstone.\n", 25 }));
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));

    add_prop(OBJ_S_WIZINFO, "This gem can be inserted in to masterwork " +
        "armours crafted by Theros Ironfeld in Solace, Krynn. When " +
        "inserted and activated, the wearer gains the see invisible " +
        "ability. The armour can be found at " +
        "/d/Krynn/common/warfare/rewards/masterwork_warfare_armour.c \n");
}


