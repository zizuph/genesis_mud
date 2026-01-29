/* quabone: A light Athasian club variant */
inherit "/d/Kalad/std/weapon";
#include <wa_types.h>
#include "defs.h"

void create_weapon()
{
    ::create_weapon();
    set_name ("quabone");
    set_short("old quabone");
    set_long ("Though a relatively poor weapon, the use of quabones (a club "+
              "formed by lashing four bones together and sharpening their "+
              "ends) in the arenas of Athas have given them some measure of "+
              "popularity.\n");
    set_adj  ("old");

    set_hit(7);
    set_pen(5);

    likely_dull=30;
    likely_corr=30;
    likely_break=30;

    set_wt(W_CLUB);
    set_dt(W_IMPALE | W_BLUDGEON);
    set_hands(W_ANYH);
    add_prop(OBJ_I_WEIGHT, 1800);
    add_prop(OBJ_I_VOLUME, 1000);
}
