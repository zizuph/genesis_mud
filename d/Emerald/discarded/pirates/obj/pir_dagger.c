inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void
create_weapon()
{
   set_name("dagger");
   set_adj("ornate");
   set_adj("golden");
   set_short("ornate golden dagger");
   
   set_long(break_string("This golden dagger is a lost relic "+
         "from a kingdom long past. The blade has been "+
         "enhanced by lining the edge with a diamond "+
         "coating. The handle's appearence is complemented "+
         "by an assortment of fine gems.\n",76));
   
   set_default_weapon(25, 25, W_KNIFE, W_SLASH | W_IMPALE,
      W_ANYH,  0);
   add_prop(OBJ_I_WEIGHT, 1790); 
   add_prop(OBJ_I_VOLUME,  1860);
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(25, 25) + 100 + random(150));
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
