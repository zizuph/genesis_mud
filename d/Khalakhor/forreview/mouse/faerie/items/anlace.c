/* weapon coded by Elizabeth Cook/Mouse, September 1996 */

inherit "/std/weapon";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include "../../mouse.h"

   void create_weapon() {
     set_name("anlace");
     add_name("dagger");
     set_short("anlace of Hypaethra");
     set_long("A finely crafted dagger with two exceedingly "+
          "sharp edges. The blade is intricately etched with "+
          "a scene depicting a disfigured soul enduring the "+
          "fiery torments of Hell. The narrow hilt has two "+
          "rather large and beautiful rubies inlaid on each "+
          "side.\n");
     set_wt(W_KNIFE);
     set_dt(W_SLASH|W_IMPALE);
     set_hit(16);
     set_pen(10);
     add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(16,10));
     add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);
     
}
    
