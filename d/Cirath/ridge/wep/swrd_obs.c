/* swrd_obs: A cool stone sword */
inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "defs.h"

void create_weapon()
{
    set_name ("sword");
    set_long ("Though less sturdy, it is widely known that weapons made of "+
              "obsidian stone are sharper then those made of most metals. "+
              "There is also something pleasently ominous about the glossy "+
              "black surface of such weapons.\n");
    add_adj  ("obsidian");
    set_adj  ("glossy");

    set_hit(19);
    set_pen(21);
    likely_dull=20;
    likely_corr=20;
    likely_break=20;

    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);
    set_hands(W_ANYH);
    add_prop(OBJ_I_WEIGHT, 1350);
    add_prop(OBJ_I_VOLUME, 800);
}
