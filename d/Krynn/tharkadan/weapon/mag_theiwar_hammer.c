inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_weapon()
{
    set_name("warhammer");
    add_name("hammer");
    add_name("club");
    set_adj("star");
    add_adj("metal");
    set_short("star metal warhammer");
    set_long("This is a dwarven warhammer made of the rare ore " +
        "referred to by ancient alchemists as 'star metal' - a blue " +
        "ore of extraordinary strength and hardness. Runes along " +
        "the head of the warhammer seem to glisten darkly.\n");

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC,({50,"enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({"This is a warhammer crafted by the " +
         "smiths of the Theiwar clan out of the rare star metal, and " +
         "enchanted by dark dwarf savants to be a warhammer of " +
         "exceptional strength and lightness.\n",15}));
    add_prop(OBJ_S_WIZINFO, "This weapon has high hit/pen, and reduced " +
         "chance of dulling, corroding, and breaking. Has a chance of " +
         "spawning on the cocoon corpse dropped by the giant spider " +
         "in the Tharkadan mountain range caverns, " +
         "/d/Krynn/tharkadan/obj/cocoon_corpse.c\n");

    set_likely_dull(1);
    set_likely_corr(1);
    set_likely_break(1);
    set_default_weapon(40, 45, W_CLUB, W_BLUDGEON, W_ANYH);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_WEIGHT, 8000);
}
