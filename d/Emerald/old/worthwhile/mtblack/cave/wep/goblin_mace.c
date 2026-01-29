/* A spiked mace - Tulix III, recoded 13/07/95 */
/* This weapon is used by /d/Emerald/cave/mon/.c */

inherit "/std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
                               
public void
create_weapon()
{
    set_name("mace");
    set_pname("maces");
    add_pname("weapons");
    set_short("spiked mace");
    set_pshort("spiked maces");
    set_adj("spiked");
    add_adj("goblin");
    set_long("It's large metal club, with sharp spikes at the "  
        + "end to make it even better at hurting people. " 
        + "It looks crafted by Goblin hands.\n");

    set_hit(19); /* Goblin made      -1 */
    set_pen(17);

    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_ANYH);
    
    add_prop(OBJ_I_WEIGHT, 6000);
    add_prop(OBJ_I_VOLUME, 1500);
}
