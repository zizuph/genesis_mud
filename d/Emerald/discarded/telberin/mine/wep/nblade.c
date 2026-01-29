 
/* mine/wep/nblade.c is cloned by mine/npc/dewarlord.c */
 
inherit "/std/weapon";

#pragma save_binary
#include <wa_types.h>
#include <stdproperties.h>
 
void
create_weapon()
{
    set_name("blade");
    add_name("sword");
    set_short("night blade");
    set_long("This dark obsidian blade is as keen as the day "+
             "it was forged from volcanic rock. You feel a presence, "+
             "alien and dark, within the blade as you touch it.\n");
    set_adj("night");
 
    set_default_weapon(29, 25, W_SWORD, W_SLASH | W_IMPALE,
                       W_ANYH,  0);
    add_prop(OBJ_I_WEIGHT, 4700);
    add_prop(OBJ_I_VOLUME,  860);
    add_prop(OBJ_I_VALUE, 1127 + random(10));
 
}
 
