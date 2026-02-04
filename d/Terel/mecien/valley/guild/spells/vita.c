#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>


#define TO this_object()
#define TP this_player()
#define EN environment
#define ENV environment

vita(string str){
   
   object who, oil;
   
   if(!str) return 0;
   who = present(str, EN(TP));
   if(!who) return 0;
   if(!living(who)) return 0;
   
   if(TP->query_skill(SS_ELEMENT_LIFE) + TP->query_skill(SS_FORM_CONJURATION) <
   random(150)) return "The holy spirits of life fail to hear thy voice.\n";
  oil = present("sacred_oil", TP);
  if(!oil) return "You will need the sacred oil.\n";
  if(TP->query_mana() < 250) return "You do not have the strength.\n";
   who->catch_msg(QCTNAME(TP) + " touches your forehead with sacred oil and speaks arcane words.\n");
   tell_room(EN(TP), QCTNAME(TP) + " touches the forehead of " + QTNAME(who) +
      " with oil and speaks some arcane words.\n", ({ who, TP }));
   TP->catch_msg("You touch the forehead of " + QTNAME(who) + 
      " with the sacred oil and speak the holy words.\n");
   
    set_alarm(3.0, -1.0, "trib", TP);
   set_alarm(5.0, -1.0, "healing", who);
   TP->set_mana(-250);
   TP->catch_msg("The vial of sacred oil burns into nothingness.\n");
  oil->remove_object();
   
   return 1;
   
}

trib(object me){
   tell_room(ENV(me), QCTNAME(me) + " turns white and begins to shake.\n", me);
  me->catch_msg("You catch a glimpse of some holy power that terrifies you!\n");
}

healing(object who){

tell_room(ENV(who), "Suddenly there is a bright blue light all about and a " +
"eerie song echoes from beyond.\n");
set_alarm(3.0, -1.0, "heal_me", who);
}

heal_me(object who){
tell_room(ENV(who), QCTNAME(who) + " is surrounded by a bluish glow.\n", who);
who->catch_msg("A great energy enters you, a sense of life and strength begin " +
"to take hold within you.\n");
who->heal_hp(75);
  if((who->query_hp()) < who->query_max_hp()){
   set_alarm(4.0, -1.0, "healing", who);
}
}


