/*
 * Modified 2021-03-02 by Carnak:
 * - Reduced the hit and pen from 50 to 40 in accordance with the
 *   rules for non magical weaponry.
 */
inherit "/std/weapon";
#include <stdproperties.h>
#include <formulas.h>

query_value(){ return 30; }

create_weapon(){
    set_name("club");
    set_adj("iron-banded");
  set_long(
  "It is a gigantic club cut from the limb of a tree. It is\n"
   +"bound with iron bands, making it heavier and deadlier.\n"
    );
    set_hit(40);
    set_pen(40);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    add_prop(OBJ_I_WEIGHT, 30000);
    add_prop(OBJ_I_VOLUME, 10000);
}
