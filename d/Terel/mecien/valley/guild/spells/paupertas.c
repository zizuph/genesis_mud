#include <stdproperties.h>
#include <money.h>
#include <ss_types.h>
#include <macros.h>

#define TP this_player()
#define TO this_object()
#define EN environment


paupertas(string str){
   object who;
   if(!str) return "Your call is unheard.\n";
   who = present(str, EN(TP));
   if(!who) return "Your call is unheard.\n";
   if(!living(who)) return "Your call is unheard.\n";
   
   if(TP->query_mana() < 120) return "You do not have the strength.\n";
   
   
   if(TP->query_skill(SS_FORM_CONJURATION) + TP->query_skill(SS_SPELLCRAFT)
         + random(100) < 200) return "Your call is unheard.\n";
   
   TP->add_mana(-120);
   
   set_alarm(5.0, -1.0, "spirits", who);
  TP->catch_msg("You call upon the enchanted spirits of the ancient world to come forth and use their mighty charms!\n");
   tell_room(EN(TP), QCTNAME(TP) + " cries aloud, intoning some unknown hymn from ages past.\n", TP);
   return 1;
   
}

poverty(object what){
   object ob;
   int n;
   seteuid(getuid(TO));
   if(what->query_coin_type()){
      if(what->query_coin_type() == "lead") return;
      n = what->num_heap();
      ob = clone_object("/d/Terel/mecien/valley/guild/spells/fake/coins");
      ob->move(EN(what));
      what->remove_object();
      ob->set_heap_size(n);
   }
}

spirits(object who){
   
   tell_room(EN(who), "A wind suddenly enters this place, you see tiny shadowy figures moving about in circles.\n");
   set_alarm(3.0, -1.0, "encircle", who);
}

encircle(object who){
   tell_room(EN(who), "As the wind continues to blow, the tiny shadowy figures seem to encircle " + QTNAME(who) + ".\n");
   who->catch_msg("As the wind continues to blow, the tiny shadowy figures seem to encircle you, almost as if dancing about you!\n");
   if(who->query_skill(SS_SPELLCRAFT) + random(100) < 140){
      set_alarm(2.0, -1.0, "bells", who);
   }
   set_alarm(4.0, -1.0, "gone", who);
}

bells(object who){
   who->catch_msg("You hear laughter from the tiny shadows as they encircle you, suddenly they stop and the sound of tiny bells can be heard all around you!\n");
   tell_room(EN(who), "The sound of laughter can be heard, then tiny bells.\n", who);
   map(all_inventory(who), poverty);
}

gone(object who){
   who->catch_msg("You feel cold.\n");
   tell_room(EN(who), "The wind suddenly dies and the tiny shadowy figures depart quickly.\n");
}


