/* Based largely on dagger.c in the EXAMPLES. */
inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "defs.h"

void create_weapon()
{
    set_name ("knife");
    set_short("noble knife");
    set_long ("Made of steel rather then stone, the knives of Athasian "+
              "nobles are both lighter and more effective then the stone "+
              "daggers others are forced to use.\n");
    set_adj  ("noble");

    set_hit(12);
    set_pen(9);

    set_wt(W_KNIFE);
    set_dt(W_SLASH | W_IMPALE);
    set_hands(W_ANYH);
    add_prop(OBJ_I_WEIGHT, 225);
    add_prop(OBJ_I_VOLUME, 32);
}
