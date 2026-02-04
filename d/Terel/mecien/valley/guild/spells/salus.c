/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#define PATH "/d/Terel/mecien/valley/guild/spells/"
#define TP this_player()

object angel;

nomask mixed
salus(string str){
   
   object caster, who, form;
   
   
   if(!str)
      return "Who do you call these blessing upon?\n";
   
   who=find_living(str);
   angel=clone_object(PATH + "angel");
  angel->move_living("X", environment(TP));
  angel->command("say I shall seek out this chosen one" +
      " and bring the blessings " +
  "of the Ancients upon them");
  angel->move_living("X", "/d/Terel/mecien/workroom");
   caster = TP;
  if(!who){
   set_alarm(10.0, -1.0, "not_found", caster);
   return 1;
   }
   set_alarm(20.0, -1.0, "do_bless", who);
   return 1;
}

do_bless(object who){
   angel->move_living("X", environment(who));
   angel->command("Hail " + who->query_name());
   angel->command("say I have been sent by " + this_player()->query_name() +
      " to bring the blessings of the Ancients upon you");
   if(who->query_alignment()>200){
      tell_room(environment(who), "The angelic spirit touches its " +
         "white mantle to " + who->query_name() + ".\n", who);
      who->catch_msg("The angelic spirit touches you with its mantle.\n");
      who->heal_hp(200);
      angel->command("say I pray the Ancients will continue to bless you");
   set_alarm(3.0, -1.0, "bye");
      return 1;
   }
   
   angel->command("say You are deemed unworthy, farewell");
   angel->move_living("X", environment(this_player()));
   angel->command("say I found " + who->query_objective() +
      " unworthy of the Ancient blessing");
   set_alarm(6.0, -1.0, "bye");
   return 1;
}

not_found(object caster){
  angel->move_living("X", environment(caster));
   angel->command("say I was unable to find the chosen one");
   angel->command("say Farewell");
  set_alarm(2.0, -1.0, "bye");
   return 1;
}

bye(){
  angel->move_living("X", "/d/Terel/mecien/workroom");
  angel->remove_object();
}

