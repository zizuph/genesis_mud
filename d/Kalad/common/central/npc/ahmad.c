inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";

#include "/sys/stdproperties.h"
#include "/d/Kalad/defs.h"

void
create_monster()
{
  ::create_monster();
  
  set_name("ahmad");
  set_race_name("banker");
  set_adj("scrawny");
  set_long(
    "Ahmad, the scrawny and efficient banker, is a member of the Merchant "+
    "Guild. If he likes you, he will change your money for you here, and "+
    "put it in an account. You better be nice to him. \n"
  );
  set_title("banker, and honoured member of the Merchant guild");
   
  set_stats(({25, 40, 25, 60, 60, 20}));
  set_hp(1000);
   
  add_prop(NPC_M_NO_ACCEPT_GIVE, 0);
    
  set_alignment(0);
   set_knight_prestige(-10);
   
  set_chat_time(7);
  add_chat("Will you hurry up?");
  add_chat("I'm a member of the Merchant Guild!");
  add_chat("If you have no money, then GET OUT!");
    
  set_act_time(5);
  add_act("sigh");
  add_act("grumble");
  add_act("stare");
     
}