inherit "/std/monster";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define ENV environment
#define TO this_object()
#define TP this_player()
#define PATH "/d/Terel/mecien/valley/guild/"

create_monster(){
   
   set_race_name("spirit");
   set_name("spirit");
   set_living_name("liyalas");
   set_short("spirit of light");
   set_long("A magnificent spirit, aglow with the light of the heavens. " +
      "Its body is transparent like a luminous wraith, draped in silvery "
      + "garb, it drifts and shimmers as if fading away."
   + "\n"
   );
   
   
   add_prop(OBJ_M_NO_ATTACK, 1);
   
   add_ask(({"for gift", "for light", "for light of the stars"}),
      "@@gift", 1);
   
   set_chat_time(3);
   add_chat("I am here but briefly");
   add_chat("The gift I bring is the light of the stars!");
   add_chat("Ask and ye shall receive");
   add_chat("The blessings of the Holy Star be upon you");
   
}


public string
gift()
{
   object ob;
   if(TP->query_skill(MYSTIC_RANK)!=2){
      return "say My gift is for those of this circle.";
   }
   seteuid(getuid());
   ob = clone_object(PATH + "obj/pendant");
   ob->move(TP);
   TP->catch_msg("You sense that some light is now with you.\n");
   return "emote holds out its hands in prayer.";
}

enter_env(object dest, object from){
::enter_env(dest, from);
set_alarm(33.0, -1.0, "bye");
}

bye(){
TO->command("say The time for me has come, I must return");
TO->command("emote returns to the heavens in a flash of light.");
TO->remove_object();
}

