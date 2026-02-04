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
     set_short("iron sword");
     set_long("The sword is forged of iron and looks very sharp.\n");
     set_adj("iron");

     set_hit(20);
     set_pen(20);
     add_prop(OBJ_I_WEIGHT, 12000);
     add_prop(OBJ_I_VOLUME, 9000);

     set_wt(W_SWORD);
     set_dt(W_SLASH | W_IMPALE);

     set_hands(W_ANYH);
}
