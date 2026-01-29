 
/* mine/wep/axe.c is cloned by mine/npc/dwarf?.c */
 
inherit "/std/weapon";

#pragma save_binary
#include <stdproperties.h>
#include <wa_types.h>
 
void
create_weapon()
{
    set_name("axe");
    set_short("metal axe");
    set_long( "This is a pretty plain metal axe.\n" );
    set_adj("metal");
 
    set_default_weapon(14, 14, W_AXE, W_SLASH | W_BLUDGEON,
                       W_LEFT,  0);
    add_prop(OBJ_I_WEIGHT, 1500);
    add_prop(OBJ_I_VOLUME,  495);
    add_prop(OBJ_I_VALUE, 125 + random(5));
}
 
