/* axe_hevy: A massive two handed stone cleaver. */
inherit "/d/Kalad/std/weapon";
#include <wa_types.h>
#include "defs.h"

void create_weapon()
{
    ::create_weapon();
    set_name ("axe");
    set_short("massive stone axe");
    set_long ("This lethal weapon relies on its extreme weight to slam "+
              "the sharpened stone blade deep into the target.  Judging "+
              "from the dried blood and bone fragments, it is not new to "+
              "this job.\n");
    set_adj  ("massive");
    add_adj  ("stone");

    set_hit(20);
    set_pen(35);
    likely_dull=20;
    likely_corr=20;
    likely_break=20;

    set_wt(W_AXE);
    set_dt(W_SLASH | W_BLUDGEON);
    set_hands(W_BOTH);
    add_prop(OBJ_I_WEIGHT,9000);
    add_prop(OBJ_I_VOLUME,1500);
}
