/* gythka: The dreaded polearm of the thri-kreen */
inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "defs.h"

void create_weapon()
{
    set_name ("gythka");
    set_short("stone gythka");
    set_long ("The frightening weapon developed and used by the Thri-Kreen "+
              "raiders for use against non-insectoid foes, the gythka is "+
              "ideally suited to the mantis warriors. It combines a thick "+
              "wooden shaft with slashing stone blades on each end, each "+
              "sharpened to a fine point for thrusting, or worse yet, "+
              "throwing. Of course, only they have mastered its use.\n");
    set_adj  ("stone");

    set_hit(15);
    set_pen(25);

    likely_dull=5;
    likely_corr=5;
    likely_break=5;

    set_wt(W_POLEARM);
    set_dt(W_SLASH | W_IMPALE | W_BLUDGEON);
    set_hands(W_BOTH);
    add_prop(OBJ_I_WEIGHT, 5400);
    add_prop(OBJ_I_VOLUME, 1100);
}
