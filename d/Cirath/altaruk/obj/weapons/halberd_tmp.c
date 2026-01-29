inherit "/std/weapon";
#include "/sys/wa_types.h"
#include <stdproperties.h>

void create_weapon()
{
    set_name ("halberd");
    set_pname("halberds");
    set_adj  ("stone-headed");
    set_short("stone-headed halberd");
    set_pshort("stone-headed halberds");
    set_long ("A halberd with a wide obsidian head.\n");

    set_hit(20);
    set_pen(25);
    likely_dull=30;
    likely_corr=-1;
    likely_break=30;

    set_wt(W_POLEARM);
    set_dt(W_IMPALE|W_SLASH);
    set_hands(W_ANYH);
    add_prop(OBJ_I_WEIGHT,3500);
    add_prop(OBJ_I_VOLUME,1500);
}
