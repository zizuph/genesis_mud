/*
 *  An enchanted diamond that can be inserted in to masterwork
 *  weapons to improve the weapon pen.
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
    config_gems("diamond", "diamonds", "ellipse-shaped blue", 6048,
        GEM_EXTREMELY_RARE, 1, 2);
    add_name("_crystal_of_demolition");
    set_random_placement(0);
    add_adj("ellipse");
    add_adj("blue");
    add_adj("shaped");
    set_long("@@default_gem_long@@ Diamond is a rare, "+
        "brilliant gem of incredible hardness and durability. " +
        "This ellipse-shaped diamond is a brilliant royal blue, " +
        "with what looks like a tiny star-metal hammer somehow " +
        "imbedded at its center.\n");

    add_prop(MAGIC_AM_ID_INFO, ({ "This ellipse-shaped diamond " +
        "is an enchanted Crystal of Demolition, and when inserted " +
        "in to a weapon specifically designed by a master smith " +
        "it will enhance it, making it more damaging when a hit " +
        "is struck.  This effect extends to providing additional " +
        "spell power for staves, daggers and wands.\n", 25 }));
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));

    add_prop(OBJ_S_WIZINFO, "This gem can be inserted in to masterwork " +
        "weapons crafted by Theros Ironfeld in Solace, Krynn. When " +
        "inserted, the weapon pen value increases 10. Spell power " +
        "is also increased by 10. The weapon code can be found at " +
        "/d/Krynn/common/warfare/rewards/masterwork_warfare_weapon.c \n");
}


