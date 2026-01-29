/* impl_st: A metal version of the bone impaler */
inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "defs.h"

void create_weapon()
{
    set_name ("impaler");
    add_name("axe");
    set_short("steel impaler");
    set_long ("Attaching a metal blade across the top of a four foot wooden "+
              "shaft has produced this lethal weapon: A dangerous new "+
              "form of axe found solely in Athas...For now.\n");
    set_adj  ("steel");

    set_hit(17);
    set_pen(19);

    set_wt(W_AXE);
    set_dt(W_IMPALE);
    set_hands(W_ANYH);
    add_prop(OBJ_I_WEIGHT,4500);
    add_prop(OBJ_I_VOLUME,650);
}
