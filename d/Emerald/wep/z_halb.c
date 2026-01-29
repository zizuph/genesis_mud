inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void
create_weapon()
{
   set_name("assagai");
   set_short("iron assagai");
   set_long(break_string("This large polearm, made for totally braining "+
	"the enemy is made of pig iron, the crudest form that is really "+
	"possible.\n", 76));
   set_adj("spirit");
   
   set_default_weapon(34, 37, W_POLEARM, W_BLUDGEON,  
      W_BOTH,  0);
   add_prop(OBJ_I_WEIGHT, 3104); 
   add_prop(OBJ_I_VOLUME, 1540); 
   add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(34, 37) + random(114) + 27);
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
