
/* mine/wep/odag.c is cloned by mine/npc/chaoslord.c */

inherit "/std/weapon";

#pragma save_binary
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Emerald/defs.h"

void
create_weapon()
{
   set_name("dagger");
   set_short("onyx dagger");
   set_long( "This glittering black blade is made of onyx, "+
      "the magical material taking your breath away with it's sheer "+
      "beauty and elegance.\n" );
   set_adj("onyx");
   
   set_default_weapon(17, 16, W_KNIFE, W_SLASH | W_IMPALE,
      W_ANYH,  this_object());
   add_prop(OBJ_I_WEIGHT, 1131);
   add_prop(OBJ_I_VOLUME,  5767);
   add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
   add_prop(OBJ_I_VALUE, 349 + random(94));
   
   
   add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));
   add_prop(MAGIC_AM_ID_INFO, ({
            "The blade is protected by a weak magical aura that accepts only a"+
            " skilled master.\n", 10,
            "Wielded by skilled hands this delicate dagger is a truely "+
            "deadly weapon.\n", 15,
            "Forged by the mightiest of chaoslords, it possesses a"+
            " strength that can shear through armours without reciving a nick"+
            " in its razor edge.\n", 25,
            "No other magical properties are given by the blade.\n", 40}));
   add_prop(OBJ_S_WIZINFO,  "A small but long dagger obtained "+
      "from the chaoslord in the Emerald mines. It is quite expensive "+
      "and is made of onyx, a rare material only found in the mines "+
      "along with emeralds.\n" );
}

public int
wield(object wep)
{
   if(this_player()->query_skill(SS_WEP_KNIFE) < 45)
      {
      write("Something within the knife seems to resists you.\n");
      return -1;
   }
   return 0;
}

