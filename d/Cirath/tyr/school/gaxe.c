inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/d/Cirath/common/defs.h"

void create_weapon()
{
    set_name ("axe");
    set_short("large obsidian axe");
   set_long("This is the standard obsidian axe used by the "
	+"guards of the Warrior's School of Tyr.  The large "
	+"obsidian head looks to have been sharpened carefully "
	+"to ensure that it slices through flesh easily.  In "
	+"the right hands, this could probably do quite "
	+"a bit of damage.\n");
    set_adj("large");
	set_adj("obsidian");

    set_hit(35);
    set_pen(25);
//    likely_dull=30;
//    likely_corr=30;
//    likely_break=30;

    set_wt(W_AXE);
    set_dt(W_SLASH);
    set_hands(W_ANYH);
    add_prop(OBJ_I_WEIGHT,5000);
    add_prop(OBJ_I_VOLUME,3300);
}
