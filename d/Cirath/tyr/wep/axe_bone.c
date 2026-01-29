/* axe_bone: A decent axe, but likely to break. */
inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "defs.h"

void create_weapon()
{
    set_name ("axe");
    set_pname("axes");
    set_short("bone axe");
    set_pshort("bone axes");
    set_long ("Formed from the sharpened jawbone of a lizard, this axe is "+
              "easy to wield, but lacks the satisfying weight of sturdier "+
              "material.\n");
    set_adj  ("bone");

    set_hit(15);
    set_pen(10);
    likely_dull=30;
    likely_corr=30;
    likely_break=30;

    set_wt(W_AXE);
    set_dt(W_SLASH);
    set_hands(W_ANYH);
    add_prop(OBJ_I_WEIGHT,1575);
    add_prop(OBJ_I_VOLUME,550);
}
