#include "../defs.h"

inherit MONASTERY_DIR + "wep/reaver_weapon";

#include <ss_types.h>
#include <wa_types.h>

void
create_reaver_weapon()
{
    set_name("axe");
    
    set_long("A large, two-handed axe with a flawless silver blade.  The " +
        "thick, sturdy handle is wrapped with strips of black leather " +
        "intertwined in such a way as to provide an excellent grip on the " +
        "weapon.  The head of the weapon consists of a large, silver " +
        "blade with a heavy, rounded bludgeoning end; the smooth silver " +
        "seems to catch even the most meager ray of light, giving the " +
        "blade an eery luminescense.\n");

    set_wt(SS_WEP_AXE);
    set_dt(W_SLASH | W_BLUDGEON);
}

