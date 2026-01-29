/*
 *  An enchanted diamond that can be inserted in to masterwork
 *  weapons to improve the weapon hit and pen.
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
    config_gems("diamond", "diamonds", "ellipse-shaped azure", 6048,
        GEM_EXTREMELY_RARE, 1, 2);
    add_name("_crystal_of_weaponry");
    set_random_placement(0);
    add_adj("ellipse");
    add_adj("azure");
    add_adj("shaped");
    set_long("@@default_gem_long@@ Diamond is a rare, "+
        "brilliant gem of incredible hardness and durability. " +
        "This ellipse-shaped diamond is a light blue azure, " +
        "with what looks like a tiny orb of gold somehow " +
        "imbedded at its center.\n");

    add_prop(MAGIC_AM_ID_INFO, ({ "This ellipse-shaped diamond " +
        "is an enchanted Crystal of Weaponry. While not providing " +
        "as powerful an effect as a Crystal of Domination or a " +
        "Crystal of Striking, it does provide the benefit of both " +
        "when inserted in to a weapon specifically designed " +
        "by a master smith it will enhance it, making it " +
        "easier to strike with and more damaging when a hit " +
        "is struck. This effect extends to providing additional " +
        "spell power for staves, daggers and wands.\n", 25 }));
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));

    add_prop(OBJ_S_WIZINFO, "This gem can be inserted in to masterwork " +
        "weapons crafted by Theros Ironfeld in Solace, Krynn. When " +
        "inserted, the weapon hit and pen value increases by 5. " +
        "Spell power by 10. The weapon code can be found at " +
        "/d/Krynn/common/warfare/rewards/masterwork_warfare_weapon.c \n");
}


