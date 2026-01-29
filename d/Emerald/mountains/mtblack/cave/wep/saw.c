/* A large saw - Tulix III, recoded 13/07/95 */
/* This weapon is used by /d/Emerald//lumberjack.c */

inherit "/std/weapon";
#include <stdproperties.h>
#include <wa_types.h>

public void
create_weapon()
{
    
    set_name("saw");
    add_pname("weapons");
    set_short("large saw");
    set_adj("large");
    set_long("A lumberjack would use this to cut down trees.\n");  
    
    set_hit(10);
    set_pen(12);
    set_wt(W_SWORD); /* Nearest to a sword */
    set_dt(W_SLASH); /* Its a saw, so slash damage only */
    set_hands(W_ANYH);
    
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 1000);
    
}
