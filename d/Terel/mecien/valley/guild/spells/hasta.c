#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TP this_player()
#define TO this_object()
#define EN environment


hasta(string str){
   
   object who, here;
   object staff;
   
   if(!str) return "Call to strike who?\n";
   who = present(str, EN(TP));
   if(!living(who)) return "Call to strike who?\n";
   if(!who) return "Call to strike who?\n";
   
   if(who == TP) return "Call to strike who?\n";
   if(TP->query_mana() < 80) return "You do not have the strength.\n";
   staff = present(MYSTIC_STAFF, TP);
   if(!staff) return "You will need the staff.\n";
   if(TP->query_skill(SS_FORM_CONJURATION) + TP->query_skill(SS_ELEMENT_AIR) +
         random(100) < 130) return "You fail to summon the heavenly powers.\n";
   TP->catch_msg("You raise your staff aloft, calling upon those guardians of the air to " +
      "strike down " + QTNAME(who) + "!\n");
   tell_room(EN(TP), QCTNAME(TP) + " raises aloft " + TP->query_possessive() + 
      " staff, looking upwards and chants an arcane invocation.\n", TP);
   set_alarmv(4.0, -1.0, "churn", ({ who, TP }));
   here = EN(TP);
   set_alarmv(8.0, -1.0, "strike", ({ who, TP, here }));
   TP->add_mana(-80);
   
   return 1;
   
}

churn(object who, object me){
   tell_room(EN(who), "There is a strange churning in the air above!\n");
   who->catch_msg("You sense danger!\n");
}

strike(object who, object me, object here){
   
   if(EN(me)!= here){
      who->catch_msg("You sense the danger has passed.\n");
      return 1;
   }
   
   tell_room(EN(who), "Suddenly the air swirls and twists into the shape " +
      " of a warrior spirit. It draws back a spear of light and casts it down upon " +
      QTNAME(who) + "!\n", who);
   who->catch_msg("Suddenly the air churns and twists into the shape of a warrior spirit, it looks at you, draws back a spear of light and casts it down upon you!.\n");
   who->hit_me(100 + (me->query_stat(SS_OCCUP)/2), MAGIC_DT, me, 3);
}


