/*
 *  An enchanted moonstone that can be inserted in to masterwork
 *  armours to reduce the weight of the armour.
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
    config_gems("moonstone", "moonstones", "glowing oval-shaped", 2216, 
        GEM_EXTREMELY_RARE, 1, 2);

    add_name("_greater_featherweight_crystal");
    set_random_placement(0);
    add_adj("oval");
    add_adj("shaped");
    add_adj("oval-shaped");
    add_adj("glowing");
    set_short("glowing oval-shaped moonstone");

    set_long("@@default_gem_long@@ Moonstone is an opalescent "+
        "pearly-blue semi-precious stone. Its name is derived "+
        "from the billowy, floating light effect produced when "+
        "it is moved. It is the perfect hardness for carving, "+
        "and requires very little polishing to produce a lustrous "+
        "sheen. This moonstone radiates a soft glow, and seems " +
        "to almost hover in your hand.\n");

    add_prop(OBJ_I_LIGHT, LIGHT_PASSIVE);
    add_prop(MAGIC_AM_ID_INFO, ({ "This oval-shaped moonstone " +
        "is an enchanted Greater Featherweight Crystal, and when inserted " +
        "in to armour specifically designed by a master smith it will " +
        "reduce the weight of the armour noticeably.\n", 25 }));
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));
    add_prop(OBJ_S_WIZINFO, "This gem can be inserted in to masterwork " +
        "armours crafted by Theros Ironfeld in Solace, Krynn. When " +
        "inserted, the wearer's armour weight is reduced by 75%. " +
        "Other similar weight reduction gems will have no further " +
        "impact on the weight of the armour. The armour can be found at " +
        "/d/Krynn/common/warfare/rewards/masterwork_warfare_armour.c \n");
}
