/* Undead Monk Initiate - Karath...Opening Day */

#include "../defs.h"

inherit MONK_BASE;

void
create_monk()
{
    set_adj(({ "strong", "growling", "repulsive", "lumbering" })[random(4)]);

    set_long("This unfortunate soul seems to be what is left of what was a "+
	"monk of the abbey in life. Some strange, perhaps evil, power has "+
	"left it caught between life and death. Strips of flesh are falling "+
	"off its limbs, revealing a strangely intact muscle structure "+
	"underneath, and it gives off a horrid stench.\n");

    set_monk_level(90);

    set_special_attack_percent(20);
    add_special_attack(palm, 50, "palm");
    add_special_attack(sidekick, 50, "sidekick");

    if (random(2))
    {
        add_equipment(({ MONASTERY_DIR + "arm/monkrobes",
                         MONASTERY_DIR + "arm/sandals",
                         MONASTERY_DIR + "arm/fistwrap" }));
    }
    else
    {
        add_equipment(({ MONASTERY_DIR + "arm/initrobes",
                         MONASTERY_DIR + "arm/fistwrap" }));
    }
}
