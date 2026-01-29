/*
 *  An enchanted tourmaline that can be inserted in to masterwork
 *  weapons to improve the wielders SS_ELEMENT magic skill.
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
    config_gems("tourmaline", "tourmalines", "ellipse-shaped red", 1048,
        GEM_EXTREMELY_RARE, 1, 2);
    add_name("_crystal_of_fire");
    set_random_placement(0);
    add_adj("ellipse");
    add_adj("shaped");
    add_adj("red");
    set_long("@@default_gem_long@@ This tourmaline is of the " +
        "rubellite variety, a dramatic red that flares garishly " +
        "in the light. It has been carved into an ellipse shape.\n");

    add_prop(MAGIC_AM_ID_INFO, ({ "This ellipse-shaped tourmaline " +
        "is an enchanted Crystal of Fire, and when inserted " +
        "in to a weapon specifically designed by a master smith " +
        "it will enhance the wielder's elemental fire spell " +
        "skill.\n", 25 }));
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));

    add_prop(OBJ_S_WIZINFO, "This gem can be inserted in to masterwork " +
        "weapons crafted by Theros Ironfeld in Solace, Krynn. When " +
        "inserted, the wielders SS_ELEMENT_FIRE is increased by 5. " +
        "The weapon code can be found at " +
        "/d/Krynn/common/warfare/rewards/masterwork_warfare_weapon.c \n");
}


