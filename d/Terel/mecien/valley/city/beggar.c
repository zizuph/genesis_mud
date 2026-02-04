/* Chatting monster */

inherit "/std/monster";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

#define TO this_object()

enter_inv(object ob, object from){
   ::enter_inv(ob, from);
   if(living(from)){
      if(ob->query_value()){
         set_alarmv(3.0, -1.0, "thank_person", ({ ob, from }));
      }
   }
}

thank_person(object ob, object from){
   command("thank " + from->query_real_name());
   if(ob->query_value() > 100){
      if(present("key")) command("give key to " + from->query_real_name());
   }
}

create_monster()
{
   set_name("beggar");
   add_name("old man");
   add_name("man");
   set_short("beggar");
   set_long("A poor suffering man. He has no teeth.\n");
   
   set_skill(SS_AWARENESS, 150);
   set_chat_time(5);
   add_chat("Help me");
   add_chat("Could you spare me something?");
   add_chat("Give to the poor!");
   add_cchat("A pox be upon you!");
  add_prop(NPC_M_NO_ACCEPT_GIVE, 0);
   clone_object("/d/Terel/mecien/valley/hforest/bwkey")->move(TO);
   set_alignment(250);
}

