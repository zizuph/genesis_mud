/* Undead Monk Initiate - Karath...Opening Day */

#include "../defs.h"

inherit MONK_BASE;

void
create_monk()
{
    set_adj(({ "small", "short", "clumsy", "slow", "shuffling" })[random(5)]);

    set_long("This unfortunate soul seems to be what is left of what was a "+
        "monk initiate in life. Some strange, perhaps evil, power has left "+
        "it caught between life and death. Strips of flesh are falling off "+
        "its limbs, and it gives off a horrid stench.\n");

    set_monk_level(70);

    if (random(2))
    {
        add_equipment(({ MONASTERY_DIR + "arm/initrobes",
                         MONASTERY_DIR + "arm/sandals" }));
    }
    else
    {
        add_equipment(({ MONASTERY_DIR + "arm/initrobes" }));
    }

    set_special_attack_percent(15);
    add_special_attack(palm, 100, "palm");
}
