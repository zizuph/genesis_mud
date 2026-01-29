/* One-handed standard arena spear */

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name("harpoon");
    set_adj("one-handed");
    set_short("one-handed harpoon");
    set_long("This is a nasty looking harpoon, tipped with a jagged point. " +
       "It is heavy yet well balanced, suited for battling thick-skinned " +
       "sea creatures.\n");
    set_default_weapon(30, 30, W_POLEARM, W_IMPALE, W_ANYH);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_WEIGHT, 4000);
}

