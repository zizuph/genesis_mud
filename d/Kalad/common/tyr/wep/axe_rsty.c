/* axe_rsty: Wonderful! A metal axe....But likely to break. */
inherit "/d/Kalad/std/weapon";
#include <wa_types.h>
#include "defs.h"

void create_weapon()
{
    ::create_weapon();
    set_name ("axe");
    set_short("rusty axe");
    set_long ("With metal as rare as it is in Athas, quality becomes less "+
              "important. This weapon should serve well, while it lasts.\n");
    set_adj  ("rusty");

    set_hit(15);
    set_pen(10);
    likely_dull=20;
    likely_corr=50;
    likely_break=30;

    set_wt(W_AXE);
    set_dt(W_SLASH);
    set_hands(W_ANYH);
    add_prop(OBJ_I_WEIGHT,3150);
    add_prop(OBJ_I_VOLUME,700);
}
