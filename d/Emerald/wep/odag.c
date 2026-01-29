inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>

#define TP this_player()

void
create_weapon()
{
   set_name("dagger");
   set_short("onyx dagger");
   set_long(break_string("This glittering black blade is made of onyx, "+
        "the magical material taking your breath away with it's sheer "+
        "beauty and elegance.\n",76));
   set_adj("onyx");
   
   set_default_weapon(33, 30, W_KNIFE, W_SLASH | W_IMPALE,  
      W_ANYH,  this_object());
   add_prop(OBJ_I_WEIGHT, 5131); 
   add_prop(OBJ_I_VOLUME,  5767); 
   add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(33, 30) + random(94) + 57);


   add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));
   add_prop(MAGIC_AM_ID_INFO, ({ ({20,40,60,80,100}), break_string("A "+
	"long black blade is this weapon, forged by the mightiest of "+
	"chaoslords. This long weapon could enter a body and come out the "+
	"other side. No magical properties are give by it though.\n", 76)}));
   add_prop(OBJ_S_WIZINFO, break_string("A small but long dagger obtained "+
        "from the chaoslord in the Emerald mines. It is quite expensive "+
        "and is made of onyx, a rare material only found in the mines "+
        "along with emeralds.\n", 76));
}

public int
wield(object wep)
{
   if(TP->query_skill(SS_WEP_KNIFE) < 45)
      {
      write("Something within the knife seems to resists you.\n");
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
