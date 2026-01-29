/* Based largely on dagger.c in the EXAMPLES. */
inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "defs.h"

void create_weapon()
{
    set_name ("dagger");
    set_short("stone dagger");
    set_long ("A common dagger of sturdy Athasian stone.\n");
    set_adj  ("stone");

    set_hit(7);
    set_pen(10);
    likely_dull=20;
    likely_corr=20;
    likely_break=20;

    set_wt(W_KNIFE);
    set_dt(W_SLASH | W_IMPALE);
    set_hands(W_ANYH);
    add_prop(OBJ_I_WEIGHT, 338);
    add_prop(OBJ_I_VOLUME, 65);
}
