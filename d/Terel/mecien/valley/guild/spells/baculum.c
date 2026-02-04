#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TO this_object()
#define TP this_player()
#define EN environment

baculum(string str){
   object who, staff;
   
   
   if(TP->query_mana() < 50) return "You do not have the strength.\n";
   staff = present(MYSTIC_STAFF, TP);
   if(!staff) return "You will need the staff.\n";
   if(TP->query_skill(SS_FORM_ENCHANTMENT) + TP->query_skill(SS_SPELLCRAFT) +
         random(100) < 150) return "Your incantation fails.\n";
   if(!str) return "Cast your staff where?\n";
   who = present(str, EN(TP));
   if(!who || who == TP) return "You find no such person.\n";
   TP->catch_msg("You make a sacred incantation and cast your staff down at " + QTNAME(who) + ".\n");
   tell_room(EN(TP), QCTNAME(TP) + " holds a staff aloft, makes a loud incantation and throws the staff down before " + QTNAME(who) + ".\n", ({ who, TP }));
   who->catch_msg(QCTNAME(TP) + " holds aloft a staff and throws it down before you.\n");
   
   set_alarmv(2.0, -1.0, "explo", ({ who, staff }));
   TP->add_mana(-50);
   staff->move(EN(TP));
   return 1;
}

explo(object who, object staff){
   
   tell_room(EN(staff), "The staff explodes into a ball of fiery white light!\n");
   tell_room(EN(staff), QCTNAME(who) + " is burned by the light.\n", who);
   who->catch_msg("You are burned by the light!\n");
   who->hit_me(50 + staff->query_mana() + random(50), MAGIC_DT, TP, -1);
   staff->add_mana(-(staff->query_mana()));
   if(random(10) > 4) staff->destroy_staff();
}


