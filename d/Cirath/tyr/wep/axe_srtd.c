/* axe_srtd: A dangerous metal one handed axe. */
inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "defs.h"

void create_weapon()
{
    set_name ("axe");
    set_short("serrated steel axe");
    set_long ("Athasian craftman have always lavished special attention on "+
              "steel creations: They can't afford shoddy workmanship when "+
              "the material is so valuable. No exception is this fine "+
              "weapon; with a flesh tearing edge and excellent balance, it "+
              "seems to cry to be used in battle.\n");
    set_adj  ("steel");
    add_adj  ("serrated");

    set_hit(22);
    set_pen(26);

    set_wt(W_AXE);
    set_dt(W_SLASH);
    set_hands(W_ANYH);
    add_prop(OBJ_I_WEIGHT,4500);
    add_prop(OBJ_I_VOLUME,650);
}
