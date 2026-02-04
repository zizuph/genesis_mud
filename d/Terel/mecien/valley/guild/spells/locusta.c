#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h";

#define TP this_player()
#define ENV environment

mixed
locusta(string str){
   
   object me, target;
   
   
   if(!str) return "Where do you desire them to go?\n";
   
   me = TP;
   target=find_living(str);
   if(!target) return "The dark spirits of plague can find no such person.\n";
    if(!target->query_skill(CURSED)) return "Such powers may only be invoked upon the cursed.\n";
    if(!present("holy_alb", TP)) return "You will need the alb.\n";
   if(TP->query_skill(SS_FORM_CONJURATION) + TP->query_skill(SS_ELEMENT_DEATH)
    < random(100)) return "You fail to summon the dark powers.\n";
   
   write("You summon the dark spirits of plaque and send them forth.\n");
  say(QCTNAME(TP) + " raises a hand and " +TP->query_possessive() + 
    " eyes turn black as pitch.\n");
   tell_room(ENV(target), "You sense the coming of some darkness and feel it would be best to flee.\n");
   set_alarmv(15.0, -1.0, "swarm", ({ target, me }));
   
   
   return 1;
   
}

swarm(object target, object me){
   object ob;
   
  tell_room(ENV(me), QCTNAME(me) + " looks shaken.\n", me);
   me->catch_msg("You feel shaken.\n");
   ob= clone_object("/d/Terel/mecien/valley/guild/spells/locust_obj");
   ob->move_living("X", ENV(target));
  ob->set_plagued(target);
  ob->plague(target);
   set_alarm(200.0, -1.0, "bye", ob);
   
}

bye(object ob){
   ob->move_living("X", "/d/Terel/mecien/trans");
   ob->remove_object();
}
