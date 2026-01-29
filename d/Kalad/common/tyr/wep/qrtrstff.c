/* qrtrstff: No sharp edges!  Kid tested, mother approved! */
inherit "/d/Kalad/std/weapon";
#include <wa_types.h>
#include "defs.h"

void create_weapon()
{
    ::create_weapon();
    set_name ("quarterstaff");
    set_long ("Compared to the various forms of bloodletting weapons in "+
              "this land, a simple shaft of wood is rare indeed.\n");
    set_adj  ("simple");

    set_hit(18);
    set_pen(18);

    likely_dull=15;
    likely_corr=15;
    likely_break=15;

    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_BOTH);
    add_prop(OBJ_I_WEIGHT, 1800);
    add_prop(OBJ_I_VOLUME, 800);
}
