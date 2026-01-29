/* chipper: A large hammer for smashing stone chips..And skulls */
inherit "/d/Kalad/std/weapon";
#include <wa_types.h>
#include "defs.h"

void create_weapon()
{
     ::create_weapon();
    set_name ("chipper");
    set_short("stone chipper");
    set_long ("Really just a simple hammer used for breaking or evening "+
              "out large chunks of stone, its weight allows it to serve "+
              "as an adequate improvised weapon.\n");
    set_adj  ("stone");

    set_hit(10);
    set_pen(14);

    likely_dull=20;
    likely_corr=20;
    likely_break=20;

    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_ANYH);
    add_prop(OBJ_I_WEIGHT, 2700);
    add_prop(OBJ_I_VOLUME, 600);
}
