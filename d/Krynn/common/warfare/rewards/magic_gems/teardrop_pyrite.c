/*
 *  An enchanted pyrite that can be inserted in to masterwork
 *  armours to improve the wearer's resistance to earth magic.
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
    config_gems("pyrite", "pyrites", "teardrop-shaped golden", 512, 
        GEM_EXTREMELY_RARE, 46, 109);

    add_name("_greater_earth_resistance_crystal");
    set_random_placement(0);
    add_adj("teardrop");
    add_adj("shaped");
    add_adj("golden");
    set_long("@@default_gem_long@@  This mineral has a "+
        "crystalline structure but the metallic sheen of gold, "+
        "and has been a source of consternation amongst amateur "+ 
        "miners for millennia. Known as both pyrite and fools "+
        "gold, it is usually rather brittle. However this gemstone " +
        "has been beautifully carved in to a teardrop shape.\n");

    add_prop(MAGIC_AM_ID_INFO, ({ "This teardrop-shaped pyrite " +
        "is enchanted with an Earth Ward, and when inserted in to " +
        "armour specifically designed by a master smith it will " +
        "provide protection to the wearer from earth " +
        "magic.\n", 25 }));
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));

    add_prop(OBJ_S_WIZINFO, "This gem can be inserted in to masterwork " +
        "armours crafted by Theros Ironfeld in Solace, Krynn. When " +
        "inserted, the earth resistances of the wearer increases by 3. " +
        "The armour can be found at " +
        "/d/Krynn/common/warfare/rewards/masterwork_warfare_armour.c \n");
}


