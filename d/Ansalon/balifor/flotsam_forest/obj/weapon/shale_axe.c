inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
    set_name("waraxe");
    add_name("axe");
    set_adj("battle-worn");
    add_adj("neidar");
    set_short("battle-worn neidar waraxe");
    set_long("A waraxe of dwarven make. Clearly once a weapon of "+
       "envy, this ancient waraxe has been actively used since the Dwarfgate "+
       "Wars many years ago.  While far from its prime, this dwarven waraxe still "+
       "has a deadly edge that would have no trouble cleaving goblin " +
       "skulls. Along the haft of the waraxe you can make out the faint " +
       "carving of a dwarven rune for 'Ironfist'.\n");
    set_default_weapon(30, 34, W_AXE, W_SLASH, W_ANYH);
    add_prop(OBJ_I_VOLUME, 6000);
    add_prop(OBJ_I_WEIGHT, 7000);
}
