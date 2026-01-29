/* polearm: No sharp edges!  Kid tested, mother approved! */
inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "defs.h"

void create_weapon()
{
    set_name ("polearm");
    set_long ("This is a simple polearm which the militia "+
              "use as a starter weapon.\n");
    set_pname("polearms");
    set_short("simple polearm");
    set_pshort("simple polearms");
    set_adj  ("simple");

    set_hit(35);
    set_pen(35);


    set_wt(W_POLEARM);
    set_dt(W_BLUDGEON);
    set_hands(W_BOTH);
    add_prop(OBJ_I_WEIGHT, 1800);
    add_prop(OBJ_I_VOLUME, 100);
}
