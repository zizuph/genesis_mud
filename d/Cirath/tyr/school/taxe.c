inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/d/Cirath/common/defs.h"

void create_weapon()
{
    set_name ("axe");
    set_short("huge heavy axe");
   set_long("This is a very large one-handed axe.  You are "
	+"surprised that you are able to effectively use such a "
	+"heavy weapon with one hand, but the weight is "
	+"distributed very evenly throughout the entire axe.  "
	+"The head of the axe appears to be made of metal, what "
	+"kind you are not sure, but it is sharp.\n");
    set_adj("huge");
	set_adj("heavy");

   set_hit(40);
   set_pen(40);
//    likely_dull=30;
//    likely_corr=30;
//    likely_break=30;

    set_wt(W_AXE);
    set_dt(W_SLASH);
    set_hands(W_ANYH);
   add_prop(OBJ_I_WEIGHT,20000);
    add_prop(OBJ_I_VOLUME,10000);
}
