inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/d/Cirath/common/defs.h"

void create_weapon()
{
    set_name ("axe");
    set_pname("axes");
    set_short("bone training axe");
    set_pshort("bone training axes");
   set_long("This is a training axe made from bone.  Most "
	+"likely it wouldn't be too useful in a real fight, "
	+"but it would be better than nothing.\n");
    set_adj("bone");
	set_adj("training");

    set_hit(20);
    set_pen(20);
//    likely_dull=30;
//    likely_corr=30;
//    likely_break=30;

    set_wt(W_AXE);
    set_dt(W_SLASH);
    set_hands(W_ANYH);
    add_prop(OBJ_I_WEIGHT,1500);
    add_prop(OBJ_I_VOLUME,1000);
}
