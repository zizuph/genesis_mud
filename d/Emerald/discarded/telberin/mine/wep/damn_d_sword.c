 
/* mine/wep/damn_d_sword.c is cloned by mine/npc/daemonlord.c */
 
inherit "/std/weapon";
 
#include "/d/Emerald/defs.h"
#include <wa_types.h>
#include <formulas.h>
 
 
void
create_weapon()
{
   set_name("katana");
   set_short("sardonyx katana");
   set_long( "The curved surface of this beautiful blade "+
        "is synonymous with a katana, the perfect blade of the warrior. "+
        "This one has no markings on it's surface and it completely "+
        "black, made of sardonyx, one of the rarest materials to find "+
        "in the world.\n" );
   set_adj("sardonyx");
 
   set_default_weapon(22, 23, W_SWORD, W_SLASH | W_IMPALE,
      W_LEFT,  this_object());
   add_prop(OBJ_I_WEIGHT, 19560);
   add_prop(OBJ_I_VOLUME,  3600);
   add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(22, 23) + random(4) - 141);
 
   add_prop(MAGIC_AM_MAGIC, ({ 40, "enchantment" }));
   add_prop(MAGIC_AM_ID_INFO, ({({20,40,60,80,100}),  "A "+
        "glittering black blade, curved slightly is this weapon of "+
        "warriors. No mark adorns it, nor rune, yet you feel that a "+
        "magical presence is within.\n"  }));
   add_prop(OBJ_S_WIZINFO,  "This is the blade obtained from "+
        "the daemonlord in the mines of Emerald '/d/Emerald/room/mine"+
        "/chasm14'"+
        ". It is a cursed weapon but does not extend any special attacks "+
        "at all, but it just a weak weapon. The monster itself it hard "+
        "to fight and so the sword represents his hardness.\n" );
}
 
public int
wield(object wep)
{
   if(TP->query_skill(SS_WEP_SWORD) < 60)
      {
      write("The sword stings you a little, you cannot wield it.\n");
      TP->heal_hp(-50);
      return -1;
   }
   return 0;
}
 
