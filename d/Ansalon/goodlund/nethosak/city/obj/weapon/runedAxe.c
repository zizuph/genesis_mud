#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

void
create_weapon()
{   
    set_name("waraxe");
    add_name("axe");
    set_adj("runed");
    set_short("runed silver waraxe");
    set_hit(35);
    set_pen(35);
    set_wt(W_AXE);
    set_dt(W_SLASH);
    set_hands(W_AXE);
    add_prop(OBJ_I_VALUE, 200); 
   
    set_long("This is a huge waraxe, that is made "+
             "broad blades, that are extremely "+
             "sharp, you notice some strange "+
             "runes that has been burned into "+
             "them. The handle has been made "+
             "out of heavy oak wood.\n");
  
    add_item(("runes"),"The runes look elven but "+
                       "you are unable to decipher "+
                       "them.\n");
}
