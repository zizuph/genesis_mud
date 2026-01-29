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
   set_name("katana");
   set_short("sardonyx katana");
   set_long(break_string("The curved surface of this beautiful blade "+
        "is synonymous with a katana, the perfect blade of the warrior. "+
        "This one has no markings on it's surface and it completely "+
        "black, made of sardonyx, one of the rarest materials to find "+
        "in the world.\n", 76));
   set_adj("sardonyx");
   
   set_default_weapon(44, 52, W_SWORD, W_SLASH | W_IMPALE,  
      W_LEFT,  this_object());
   add_prop(OBJ_I_WEIGHT, 14560); 
   add_prop(OBJ_I_VOLUME,  1600); 
   add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(44, 52) + random(137) + 41);

   add_prop(MAGIC_AM_MAGIC, ({ 40, "enchantment" }));
   add_prop(MAGIC_AM_ID_INFO, ({({20,40,60,80,100}), break_string("A "+
	"glittering black blade, curved slightly is this weapon of "+
	"warriors. No mark adorns it, nor rune, yet you feel that a "+
	"magical presence is within.\n", 76) }));
   add_prop(OBJ_S_WIZINFO, break_string("This is the blade obtained from "+
        "the daemonlord in the mines of Emerald '/d/Emerald/room/mine"+
	"/chasm14'"+
        ". It is a magical weapon but does not extend any special attacks "+
        "at all, but it just a hard weapon. The monster itself it hard "+
        "to fight and so the sword represents his hardness.\n", 76));
}

public int
wield(object wep)
{
   if(TP->query_skill(SS_WEP_SWORD) < 70)
      {
      write("The sword stings you a little, you cannot wield it.\n");
      TP->heal_hp(-50);
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
