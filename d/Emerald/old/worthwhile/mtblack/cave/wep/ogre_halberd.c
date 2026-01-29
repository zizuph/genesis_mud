/* A large halberd - Tulix III, recoded 13/07/95 */
/* This weapon is used by /d/Emerald/cave/mon/.c */

inherit "/std/weapon";
#include <stdproperties.h>
#include <wa_types.h>

public void
create_weapon()
{
    set_name("halberd");
    set_short("large halberd");
    add_pname("weapons");
    set_adj("large");
    set_long("It's best described as an overgrown axe.\n"  
        + "It is so big that it is no longer an axe, but a polearm...\n " 
        + "it would appear to be Orc or Goblin in origin.\n");

    set_hit(26);
    set_pen(36);
    set_wt(W_POLEARM);
    set_dt(W_IMPALE);
    set_hands(W_BOTH);
    
    add_prop(OBJ_I_WEIGHT, 12000);
    add_prop(OBJ_I_VOLUME, 2500);
}
