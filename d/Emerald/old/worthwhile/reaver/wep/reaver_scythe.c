#include "../defs.h"

inherit MONASTERY_DIR + "wep/reaver_weapon";

#include <ss_types.h>
#include <wa_types.h>

void
create_reaver_weapon()
{
    set_name("scythe");
    
    set_long("A wicked scythe that was obviously specially forged to be " +
        "a truly deadly weapon rather than a simple farmer's tool.  " +
        "The thick, sturdy handle is wrapped with strips of black leather " +
        "intertwined in such a way as to provide an excellent grip on the " +
        "weapon.  Its long, curved, silver blade seems to catch even the " +
        "most meager ray of light, giving the blade an eerie luminescense.\n");

    set_wt(SS_WEP_POLEARM);
    set_dt(W_SLASH);
}

