/* impl_bn: A bone piercing weapon based on axe design */
inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "defs.h"

void create_weapon()
{
    set_name ("impaler");
    set_short("bone impaler");
    set_long ("Though wielded much like an axe, the impaler replaced the "+
              "blade with a sharpened shaft of bone. Common in the arenas "+
              "of Athas, the weapons are starting to appear elsewhere.\n");
    set_adj  ("bone");

    set_hit(14);
    set_pen(14);
    likely_dull=30;
    likely_corr=30;
    likely_break=30;

    set_wt(W_AXE);
    set_dt(W_IMPALE);
    set_hands(W_ANYH);
    add_prop(OBJ_I_WEIGHT,2250);
    add_prop(OBJ_I_VOLUME,700);
}
