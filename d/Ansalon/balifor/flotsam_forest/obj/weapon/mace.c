inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
    set_name("mace");
    set_adj("horseman's");
    set_short("horseman's mace");
    set_long("Designed for mounted combat, it is relatively " +
      "light so that the wielder can accurately hit an " +
      "enemy. Relying on the mount's momentum for damage, it " +
      "is not quite as useful for footmen, but by the looks " +
      "of things, this one could really pack a whallop.\n");
    set_default_weapon(34,25,W_CLUB,W_BLUDGEON,W_ANYH);
    add_prop(OBJ_I_VOLUME, 6000);
    add_prop(OBJ_I_WEIGHT, 6000);
}
