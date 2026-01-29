/* axe_wckd: Yes I am...... */
inherit "/d/Kalad/std/weapon";
#include <wa_types.h>
#include "defs.h"

void create_weapon()
{
     ::create_weapon();
    set_name ("axe");
    set_short("wicked steel axe");
    set_long ("Possibly the most deadly common weapon in Athas, the huge "+
              "metal head of this wicked axe represents a fine balance "+
              "between control and raw killing power achievable by only "+
              "the finest specialist in axe design.\n");
    set_adj  ("wicked");
    add_adj  ("steel");

    set_hit(35);
    set_pen(35);
    likely_dull=5;
    likely_corr=5;
    likely_break=5;

    set_wt(W_AXE);
    set_dt(W_SLASH | W_BLUDGEON);
    set_hands(W_BOTH);
    add_prop(OBJ_I_WEIGHT,6750);
    add_prop(OBJ_I_VOLUME,975);
}
