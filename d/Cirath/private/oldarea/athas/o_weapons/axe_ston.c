/* axe_ston: A moderately strong axe of stone. */
inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "defs.h"

void create_weapon()
{
    set_name ("axe");
    set_short("flaked stone axe");
    set_long ("Though made of simple stone, the flaked edge and heavy head "+
              "of this weapon more then make up for its material.\n");
    set_adj  ("stone");
    add_adj  ("flaked");

    set_hit(13);
    set_pen(18);
    likely_dull=20;
    likely_corr=20;
    likely_break=20;

    set_wt(W_AXE);
    set_dt(W_SLASH);
    set_hands(W_ANYH);
    add_prop(OBJ_I_WEIGHT,2362);
    add_prop(OBJ_I_VOLUME,600);
}
