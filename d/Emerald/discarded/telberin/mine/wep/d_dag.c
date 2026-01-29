 
/* mine/wep/d_dag.c is cloned by mine/npc/daemonlord.c */
 
inherit "/std/weapon";
 
#include "/d/Emerald/defs.h"
#include <wa_types.h>
#include <formulas.h>
 
 
void
create_weapon()
{
   set_name("dirk");
   set_short("sardonyx dirk");
   set_long( "This long throwing dagger can be used for "+
        "close quarter combat. It is forged from the magical rock sardonyx"+
        ", a rarity in itself.\n" );
   set_adj("sardonyx");
 
   set_default_weapon(34, 31, W_KNIFE, W_SLASH | W_IMPALE,
      W_ANYH,  this_object());
   add_prop(OBJ_I_WEIGHT, 5631);
   add_prop(OBJ_I_VOLUME,  5917);
   add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(34, 31) + random(94) + 57);
   add_prop(MAGIC_AM_ID_INFO, ({ ({20,40,60,80,100}),  "An "+
        "innate sense of power flows through this long weapon, it's "+
        "black blade seeming to absorb all the light in the room. It "+
        "feels warm and comforting in your hands but you feel no extra "+
        "power contained in it.\n" }));
   add_prop(OBJ_S_WIZINFO,  "A small but long dagger obtained "+
        "from the daemonlord in the Emerald mines. It is quite expensive "+
        "and is made of sardonyx, a rare material only found in the mines "+
        "along with emeralds.\n" );
}
 
public int
wield(object wep)
{
   if(TP->query_skill(SS_WEP_KNIFE) < 45)
      {
      write("The dirk glows red hot in your hand, you almost drop it.\n");
      TP->heal_hp(-50);
      return -1;
   }
   return 0;
}
 
