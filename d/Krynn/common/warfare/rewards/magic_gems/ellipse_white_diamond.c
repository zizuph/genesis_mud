/*
 *  An enchanted diamond that can be inserted in to masterwork
 *  weapons to improve the weapon hit.
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
    config_gems("diamond", "diamonds", "ellipse-shaped white", 6048,
        GEM_EXTREMELY_RARE, 1, 2);
    add_name("_crystal_of_striking");
    set_random_placement(0);
    add_adj("ellipse");
    add_adj("shaped");
    add_adj("white");
    set_long("@@default_gem_long@@ Diamond is a rare, "+
        "brilliant gem of incredible hardness and durability. " +
        "This ellipse-shaped diamond is crystal clear, with " +
        "what looks like a tiny orb of steel somehow imbedded " +
        "at its center.\n");

    add_prop(MAGIC_AM_ID_INFO, ({ "This ellipse-shaped diamond " +
        "is an enchanted Crystal of Striking, and when inserted " +
        "in to a weapon specifically designed by a master smith " +
        "it will enhance it, making it easier to successfully " +
        "hit an opponent. This effect extends to providing additional " +
        "spell power for staves, daggers and wands.\n", 25 }));
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));

    add_prop(OBJ_S_WIZINFO, "This gem can be inserted in to masterwork " +
        "weapons crafted by Theros Ironfeld in Solace, Krynn. When " +
        "inserted, the weapon hit value increases 10. Spell power " +
        "is also increased by 10. The weapon code can be found at " +
        "/d/Krynn/common/warfare/rewards/masterwork_warfare_weapon.c \n");
}


