#pragma save_binary

inherit "/std/weapon";

#include "../goblins.h"
#include <wa_types.h>

create_weapon()
{
    set_name("battleaxe"); 
    set_adj("wicked");
    
    set_short("wicked battleaxe"); 
    set_long(BSN("A broad, double edged blade is securely fastened to a " +
        "meter long haft.  The blade looks quite sharp."));

    set_wt(W_AXE);
    set_hands(W_BOTH);
    set_hit(15);
    set_pen(20);
    set_dt( W_IMPALE | W_BLUDGEON );
    
    set_default_weapon();
}