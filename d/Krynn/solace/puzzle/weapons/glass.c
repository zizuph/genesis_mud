/* A shard of glass from broken window. ~puzzle/weapons/glass */

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>

void 
create_weapon()
{
    set_name("glass");
    add_name("shard");
    set_adj("shard of");
    set_long("This is a broken piece of glass.\n");
    add_prop("mystic_weapon", 1);

    set_hit(10);

    set_wt(W_KNIFE);

    set_hands(W_BOTH);
    set_dt(W_IMPALE | W_SLASH);

    add_prop("mystic_weapon", 1);
    /* Since this is a quest item, we add the mystic
     * prop so they can do the quest as well
     */
}
