inherit "/std/weapon";
#include "/sys/wa_types.h"
#include <stdproperties.h>

void create_weapon()
{
    set_name ("spear");
    set_pname("spears");
    set_adj  ("wooden");
    set_short("wooden spear");
    set_pshort("wooden spears");
    set_long ("A sturdy pole with the sharp beak of an inix" +
        " fixed at one end.\n");

    set_hit(25);
    set_pen(30);
    likely_dull=30;
    likely_corr=-1;
    likely_break=20;

    set_wt(W_POLEARM);
    set_dt(W_IMPALE);
    set_hands(W_ANYH);
    add_prop(OBJ_I_WEIGHT,2000);
    add_prop(OBJ_I_VOLUME,1000);
}
