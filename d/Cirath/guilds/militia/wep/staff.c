/* qrtrstff: No sharp edges!  Kid tested, mother approved! */
inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "defs.h"

void create_weapon()
{
    set_name ("staff");
    set_long ("Compared to the various forms of bloodletting weapons in "+
              "this land, a simple shaft of wood is rare indeed.\n");
    set_pname("staves");
    set_short("simple staff");
    set_pshort("simple staves");
    set_adj  ("simple");

    set_hit(30);
    set_pen(30);


    set_wt(W_POLEARM);
    set_dt(W_BLUDGEON);
    set_hands(W_ANYH);
    add_prop(OBJ_I_WEIGHT, 1800);
    add_prop(OBJ_I_VOLUME, 800);
}
