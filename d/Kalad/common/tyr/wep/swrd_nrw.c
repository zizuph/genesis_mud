/* swrd_obs: A cool stone sword */
inherit "/d/Kalad/std/weapon";
#include <wa_types.h>
#include "defs.h"

void create_weapon()
{
    ::create_weapon();
    set_name ("sword");
    set_long ("To spread the supply of steel as much as possible most "+
              "swords, including this one, are made somewhat narrow. Still, "+
              "they more then make up for this by focusing on the sharpness "+
              "and quality of such weapons.\n");
    add_adj  ("steel");
    set_adj  ("narrow");

    set_hit(21);
    set_pen(23);

    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);
    set_hands(W_ANYH);
    add_prop(OBJ_I_WEIGHT, 1800);
    add_prop(OBJ_I_VOLUME, 600);
}
