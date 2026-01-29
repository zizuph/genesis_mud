inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_weapon()
{
    set_name("thighbone");
    add_name("club");
    set_adj("giant");
    set_short("stone giant thighbone");
    set_long("This is the dense thighbone of a stone giant! As large " +
       "as a two-handed warhammer, it looks harder than steel. You " +
       "imagine this weapon would cause a great deal of damage!\n");

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC,({50,"enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({"This is the thighbone of a stone " +
             "giant, and is imbued with the primal earth energies " +
             "natural to this humanoid. These energies confer a " +
             "hardness greater than forged steel, Making it do " +
             "considerably more damage than a warhammer of similar " +
             "size.\n",15}));
    add_prop(OBJ_S_WIZINFO, "This weapon has a high pen. Has a chance " +
             "of spawning on the stone giant residing in the Tharkanan " +
             "mountain range, /d/Krynn/tharkadan/"+
             "living/stonegiant.c, as a leftover.\n");

    set_default_weapon(35, 50, W_CLUB, W_BLUDGEON, W_BOTH);
    add_prop(OBJ_I_VOLUME, 8000);
    add_prop(OBJ_I_WEIGHT, 14000);
}
