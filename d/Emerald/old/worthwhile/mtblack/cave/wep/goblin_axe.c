/* A battleaxe - Tulix III, recoded 13/07/95 */
/* This weapon is used by /d/Emerald/cave/mon/.c */

inherit "/std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
                               
public void
create_weapon()
{
    set_name("battleaxe");
    add_pname("weapons");
    add_pname("battleaxes");
    add_adj("medium");
    add_adj("goblin");
    set_short("battleaxe");
    set_long("It's a medium sized battleaxe, which has "
        + "a single vertical blade. The blade is made out of iron, " 
        + "and is probably Goblin made.\n");

    add_name("axe");
    add_adj("goblin");
    set_hit(22);  /* -1 for being goblin made */
    set_pen(24);
    set_wt(W_AXE);
    set_dt(W_SLASH);
    set_hands(W_ANYH);
    
    add_prop(OBJ_I_WEIGHT, 6000);
    add_prop(OBJ_I_VOLUME, 1200);
}
