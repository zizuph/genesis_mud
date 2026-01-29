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
    set_adj("blue");
    add_adj("two-handed");
    add_adj("metal");
    set_short("blue two-handed warhammer");
    set_long("This is a massive two-handed warhammer made of the rare " +
        "ore referred to by ancient alchemists as 'star metal' - a " +
        "blue ore of extraordinary strength and hardness. The style " +
        "of this weapon's craftsmanship would indicate it is an old " +
        "hammer, likely from the days of the Dwarfgate Wars.\n");

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC,({50,"enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({"This weapon was forged before the " +
        "Cataclysm by dwarven weaponsmiths and alchemists from the " +
        "prized blue ore known as 'star metal'. This weapon is " +
        "incredibly sharp and well balanced, far superior to similar " +
        "unenchanted weapons, and is far less likely to wear or " +
        "break.\n",15}));
    add_prop(OBJ_S_WIZINFO, "This weapon has high hit/pen, and reduced " +
        "chance of dulling, corroding, and breaking. Has a chance of " +
        "spawning on the ogre barbarians of the Tharkanan mountain " +
        "range, /d/Krynn/tharkadan/living/ogre.c\n");

    set_likely_dull(1);
    set_likely_corr(1);
    set_likely_break(1);
    set_default_weapon(47, 55, W_CLUB, W_BLUDGEON, W_BOTH);
    add_prop(OBJ_I_VOLUME, 8000);
    add_prop(OBJ_I_WEIGHT, 24000);
}
