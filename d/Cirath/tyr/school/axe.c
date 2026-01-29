inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/d/Cirath/common/defs.h"

void create_weapon()
{
    set_name ("axe");
    set_pname("axes");
    set_short("wooden training axe");
    set_pshort("wooden training axes");
   set_long("This is a simple wooden training axe, used by the "
	+"adepts while practicing their forms.  It probably "
	+"wouldn't do too well in a regular fight, but it is "
	+"excellent for training.\n");
    set_adj  ("wooden");
	set_adj("training");

    set_hit(10);
    set_pen(10);
//    likely_dull=30;
//    likely_corr=30;
//    likely_break=30;

    set_wt(W_AXE);
    set_dt(W_SLASH);
    set_hands(W_ANYH);
    add_prop(OBJ_I_WEIGHT,1000);
    add_prop(OBJ_I_VOLUME,500);
}
