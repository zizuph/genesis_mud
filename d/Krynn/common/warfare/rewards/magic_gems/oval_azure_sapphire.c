/*
 *  An enchanted sapphire that can be inserted in to masterwork
 *  armours to improve the two handed combat skill.
 *
 *  Arman Kharas, October 2018
 */

inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"
#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <const.h>

void
create_gems()
{
    config_gems("sapphire", "sapphires", "oval-shaped azure", 2345, 
        GEM_EXTREMELY_RARE, 2, 4);

    add_name("_crystal_of_ambidexterity");
    set_random_placement(0);
    add_adj("oval");
    add_adj("shaped");
    add_adj("oval-shaped");
    add_adj("azure");
    set_short("oval-shaped azure sapphire");
    set_long("@@default_gem_long@@  Sapphire is a gem "+
        "of great value, brilliance, and durability. This " +
        "sapphire is a glorious azure, the colour of the sky " +
        "a clear day, and seems to pulse with arcane energy.\n");

    add_prop(MAGIC_AM_ID_INFO, ({ "This oval-shaped azure sapphire " +
        "is an enchanted Crystal of Ambidexterity, and when inserted in to " +
        "armour specifically designed by a master smith it will enhance " +
        "the two handed combat skill of the wearer.\n", 25 }));
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));
    add_prop(OBJ_S_WIZINFO, "This gem can be inserted in to masterwork " +
        "armours crafted by Theros Ironfeld in Solace, Krynn. When " +
        "inserted, the wearer's 2handed combat skill increases by 5. The " +
        "armour can be found at " +
        "/d/Krynn/common/warfare/rewards/masterwork_warfare_armour.c \n");
}


