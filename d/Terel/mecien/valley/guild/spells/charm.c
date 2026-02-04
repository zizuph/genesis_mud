inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define EN environment
#define TP this_player()
#define TO this_object()

object who;

mystic(object mystic){
   if(living(mystic)){
      if(MEMBER(mystic)){
         who->command("worship " + mystic->query_real_name());
         if(random(10) > 4) who->command("kiss " + mystic->query_real_name());
      }
   }
   
}


create_object(){
   
   set_name("_charm_");
   
   set_no_show(1);
   
   add_prop(OBJ_M_NO_DROP, 1);
   
}

charm(){
   
  int n;

   n = random(13);
   
   
   
   map(all_inventory(EN(who)), mystic);
   
   
   switch(n){
      case 0: who->command("say I love the ancient world!");
      break;
      case 1: who->command("shout I devote myself to piety and spirits, and all forms of goodness!");
      break;
      case 2: who->command("say I should be praying to holy things, songs and spirits");
      break;
      case 3: who->command("say I will worship the grass, the moon, the wild things in the berry bushes!");
      break;
      case 4: who->command("shout Weeee heee! I'm happy! The birds of Peace are free to fly! I'm soaring like the winds spirit brother!");
      break;
      case 5: who->command("say Whichever O ever a Mystic there was!");
      break;
      case 6: who->command("say I shall reverence the holy things, the beauty and peace of valleys and lakes");
      break;
      case 7: who->command("say I am filled with visions of stars and moons!");
      break;
      case 8: who->command("say Believe in ancient powers, for I live as an example!");
      break;
      case 9:  who->command("say Every Valley shall be exalted!");
      break;
      default: who->command("say I love the mystic life, I love to pray, from the Shrine to Elnoven!!!");
   }
}



bye(){
    who->catch_msg("A strange warmth leaves you.\n");
  TO->remove_object();
}

   







enter_env(object inv, object from){
   ::enter_env(inv, from);
   
   if(living(inv)){
      who = inv;
      set_alarm(5.0, 10.0, "charm");
    set_alarm(1200.0, -1.0, "bye");
   }
   
}

