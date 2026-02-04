/*
 * Based on Mortricia's plain sword
 */

inherit "/std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Terel/common/terel_std_rec.h"

void create_weapon()
{
     set_name("sword");
     set_short("steel sword");
     set_long("The sword is forged of steel and looks very sharp.\n");
     set_adj("steel");

     set_hit(22);
     set_pen(22);
     add_prop(OBJ_I_WEIGHT, 10000);
     add_prop(OBJ_I_VOLUME, 9000);

     set_wt(W_SWORD);
     set_dt(W_SLASH | W_IMPALE);

     set_hands(W_ANYH);
}
