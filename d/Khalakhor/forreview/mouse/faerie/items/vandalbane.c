/* a weapon coded by Elizabeth Cook/Mouse, October 1996 */

inherit"/std/weapon";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include "../../mouse.h"

   void create_weapon()  {
     set_name("sword");
     add_name("vandalbane");
     set_short("dark sword with winged hilt");
     set_long("The blade of this sword, now known as Vandalbane, "+
          "is strangely unreflective, having been blackened and "+
          "annealed by the sulphuric breath of the dreaded red beast, "+
          "Vandalmoor. The basket hilt is fashioned in the shape of "+
          "golden wings of a bird of prey.\n");
     set_wt(W_SWORD);
     set_dt(W_SLASH|W_IMPALE);
     set_hit(26);
     set_pen(30);
     add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(26,30));
     add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);

}
