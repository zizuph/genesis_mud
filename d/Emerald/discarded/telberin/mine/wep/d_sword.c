 
/* /d/Emerald/mine/wep/d_sword.c id cloned by /d/Emerald/mine/npc/daemonlord.c 
 */
 
inherit "/std/weapon";
 
#include "/d/Emerald/defs.h"
#include <wa_types.h>
#include <formulas.h>
 
void
create_weapon()
{
   set_name("scimitar");
   set_short("sardonyx scimitar");
   set_long( "The curved surface of this beautiful blade "+
        "is synonymous with a scimitar, the perfect blade of the warrior. "+
        "This one has no markings on it's surface and it completely "+
        "black, made of sardonyx, one of the rarest materials to find "+
        "in the world.\n" );
   set_adj("sardonyx");
 
   set_default_weapon(47, 32, W_SWORD, W_SLASH, W_LEFT, this_object());
   /* Changed from 40, 45 in interests of balance by Tulix 19/05/96. */
   add_prop(OBJ_I_WEIGHT, 14560);
   add_prop(OBJ_I_VOLUME,  1600);
   add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(44, 52) + random(137) + 41);
 
   add_prop(MAGIC_AM_MAGIC, ({ 40, "enchantment" }));
   add_prop(MAGIC_AM_ID_INFO, ({({20,40,60,80,100}),  "A "+
        "glittering black blade, curved slightly is this weapon of "+
        "warriors. No mark adorns it, nor rune, yet you feel that a "+
        "magical presence is within.\n"  }));
   add_prop(OBJ_S_WIZINFO,  "This is the blade obtained from "+
        "the daemonlord in the mines of Emerald '/d/Emerald/room/mine"+
        "/chasm14'"+
        ". It is a magical weapon but does not extend any special attacks "+
        "at all, but it just a hard weapon. The monster itself it hard "+
        "to fight and so the sword represents his hardness.\n" );
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
 
