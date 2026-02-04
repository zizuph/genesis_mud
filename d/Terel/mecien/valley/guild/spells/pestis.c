#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TP this_player()
#define TO this_object()
#define EN environment


pestis(string str){
   
   object dis, who;
   
   if(TP->query_mana() < 200) return "You do not have the strength.\n";
   if(TP->query_skill(SS_FORM_CONJURATION) + TP->query_skill(SS_ELEMENT_DEATH) +
         random(100) < 150) return "You fail to summon the dark powers.\n";
   if(!str) return "You must name a victim for the dark spirits.\n";
   who = present(str, EN(TP));
   if(!who || who == TP) return "The dark spirits find no such victim.\n";
   
   write("You call down to the spirits of darkness, asking them to bring forth their dreadful powers.\n");
   say(QCTNAME(TP) + " shudders, holding out a hand, with eyes of pitch, crying out some anguished plea.\n");
   
   set_alarm(6.0, -1.0, "disease", who);
   TP->add_mana(-200);
   return 1;
}


disease(object who){
   object dis;
   tell_room(EN(who), "Shadowy hands seem to emerge from the earth, writhing up and touching the feet and legs of " + QTNAME(who) + ".\n", who);
   dis = clone_object("/d/Terel/mecien/valley/guild/spells/plague");
   dis->move(who);
}

