inherit "/std/monster";
inherit "/std/combat/unarmed";
inherit "/std/act/chat";
inherit "/std/act/action";

#include "defs.h"


void
create_monster()
{
   if (!IS_CLONE)
      return;
   
   set_name("neptune");
   set_short("salty god");
   set_adj("salty");
   add_name("god");
   set_long("He is the god of the sea!\n");
   
   set_base_stat(SS_STR, 101 + random(99));
   set_base_stat(SS_DEX, 100 + random(75));
   set_base_stat(SS_CON, 100 + random(75));
   set_base_stat(SS_INT, 100 + random(50));
   set_base_stat(SS_WIS, 100 + random(50));
   set_base_stat(SS_DIS, 100 + random(75));
   
   heal_hp(9000);
   
   set_skill(SS_DEFENCE, 100);
   set_skill(SS_UNARM_COMBAT,100);
   set_skill(SS_BLIND_COMBAT, 100);
   set_skill(SS_ELEMENT_LIFE, 100);
   set_skill(SS_AWARENESS,100);
   
   add_prop(OBJ_I_WEIGHT, 76000);
   add_prop(CONT_I_MAX_WEIGHT, 200000);
   add_prop(OBJ_I_VOLUME, 89000);
   add_prop(CONT_I_MAX_VOLUME, 100000);
   add_prop(LIVE_I_ALWAYSKNOWN,1);
   
   set_alarm(3.0,0.0,"enter_room");
   set_alarm(6.0,0.0,"instruct");
   set_alarm(10.0,0.0,"good_bye");
   
}

int
enter_room()
{
   tell_room(ENV(TO),"Neptune coalesces from a column of water.\n");
   return 1;
}

int
instruct()
{
   tell_room(ENV(TO),"Neptne says:\n"+
      "This is the main guild room of the pirates, you may now join "+
      "by pledging your life to the cause of the "+
      "pirates. This is an island to the east of Emerald, if you wish "+
      "to get back you may swim or ask a fellow pirate. Good luck in "+
      "all your endeavors. Remember, there is honour amoung pirates.\n");
   return 1;
}

int
good_bye()
{
   tell_room(ENV(TO),"Neptune disappears in a swirl of wind and water.\n");
   TO->remove_object();
   return 1;
}
