 
/* mine/wep/halb.c is cloned by mine/npc/dwarf3.c */
 
inherit "/std/weapon";

#pragma save_binary
#include <stdproperties.h>
#include <wa_types.h>
 
void
create_weapon()
{
    set_name("halberd");
    set_short("steel halberd");
    set_long( "This large and heavy hauberk is made of "+
              "tough steel and looks deadly with the hook on the end.\n" );
    set_adj("steel");
 
    set_default_weapon(26, 39, W_POLEARM, W_SLASH | W_IMPALE, W_BOTH, 0);
    /* Changed from 24, 27 to bring in line with weapon_guide. */
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME,  860);
    add_prop(OBJ_I_VALUE, 603 + random(150));
}
 
