inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "defs.h"

void create_weapon()
{
    set_name ("knife");
    set_short("fishing knife");
    set_long ("A large knife with a sharp blade and a serrated edge." +
              "From the smell of it you know it is a fishing knife.\n");
    set_adj  ("fishing");

    set_hit(20);
    set_pen(25);
    set_wt(W_KNIFE);
    set_dt(W_SLASH | W_IMPALE);
    set_hands(W_ANYH);
    add_prop(OBJ_I_WEIGHT, 600);
    add_prop(OBJ_I_VOLUME, 120);
}
