inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include "default.h"


void
create_weapon()
{
   set_name("sword");
   set_short("onyx sword");
   set_long("This glittering black sword, is made of a magical "+
      "material found only in a few places in the world, onyx. "+
      "It's glittering black blade twinkles like the night sky.\n");
   set_adj("onyx");
   
   set_default_weapon(40, 50, W_SWORD, W_SLASH | W_IMPALE,  
      W_LEFT,  this_object());
   add_prop(OBJ_I_WEIGHT, 13560); 
   add_prop(OBJ_I_VOLUME,  1100); 
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(40, 50) + random(123) + 57);
   
}

public int
wield(object wep)
{
   if(TP->query_skill(SS_WEP_SWORD) < 70)
      {
      write("Something within the sword resists you.\n");
      return -1;
   }
   return 0;
}

string
query_recover()
{
   return MASTER + ":" + query_wep_recover();
}

void
init_recover(string arg)
{
   init_wep_recover(arg);
}
