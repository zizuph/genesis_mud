#include <macros.h>
#include <stdproperties.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h";

#define TP this_player()
#define TO this_object()
#define EN environment
#define GIFT "/d/Terel/mecien/valley/guild/obj/"

gift(object who){

 object gift;

       gift = clone_object(GIFT + "hw");
  gift->move(who);
  who->catch_msg("A spirit appears before you and places a " + gift->query_short() + " in your hand.\n");
}


evils(object who){
   if(who->query_wiz_level()) return 0;
   if(who->query_alignment() > -100) return 0;
   who->catch_msg("Some horrible darkness seems to form, you sense some terrifying power has shaken the world.\n");
   who->command("shiver");
   who->add_panic(20);
   if(random(10) > 5) set_alarm(3.0, -1.0, "blood", who);
   set_alarm(2.0, -1.0, "voices", who);
}

blood(object who){
  tell_room(EN(who), "A bit of blood issues out of the eyes of " + QCTNAME(who) + ".\n", who);
  who->catch_msg("A bit of blood issues out of your eyes.\n");
   who->add_attack_delay(60, 0);
}

voices(object who){
   tell_room(EN(who), "Eerie voices are heard from dark and mysterious clouds that seem to pass overhead.\n");
   who->catch_msg("A thundering shakes the earth about you!\n");
}

mystic(object who){
   
   if(!MEMBER(who)) return;
   
   who->catch_msg("You sense a miracle.\n");
   who->heal_hp(1000);
   who->add_panic(-100);
   if(random(10) > 5) set_alarm(3.0, -1.0, "gift", who);
   
   return 1;
   
}
mirabilis(){
   object robe, ob1, ob2, ob3, me, staff;
   
   me = TP;
   
   if((TP->query_mana()) < TP->query_max_mana()) return "You do not have the strength.\n";
   robe = present(MYSTIC_ROBE, TP);
   if(!robe) return "You will need the white robe.\n";
   if(!robe->query_worn()) return "The robe must be worn.\n";
   staff = present(MYSTIC_STAFF, TP);
   if(!staff) return "You must possess the arcane staff.\n";
   
   ob1 = present(MYSTIC_AMULET, TP);
   if(!ob1) return "You will need the amulet.\n";
   if(!EN(TP)->query_prop("mystic_presence")) return "The ancient powers must be present.\n";
   ob2 = present(MYSTIC_ICON, TP);
   if(!ob2) return "You will need the holy icon.\n";
   tell_room(EN(TP), QCTNAME(TP) + " casts " + TP->query_possessive() + 
      " arcane runed staff down upon the ground.\n", TP);
   staff->remove_prop(OBJ_M_NO_DROP);
   staff->move(EN(TP));
   ob1->remove_object();
   TP->catch_msg("Your amulet cracks into pieces.\n");
   ob2->remove_object();
   set_alarmv(6.0, -1.0, "tear", ({ robe, me }));
   set_alarm(4.0, -1.0, "stuff", me);
   set_alarm(10.0, -1.0, "echoes", me);
   set_alarm(5.0, -1.0, "bye_staff", staff);
   set_alarm(20.0, -1.0, "chosen", me);
   TP->add_mana(-(TP->query_max_mana()));
   return 1;
}

stuff(object me){
   me->catch_msg("Closing your eyes, you invoke the names of the Ancients.\n");
   tell_room(EN(me), QCTNAME(me) + " closes " + me->query_possessive() +
      " eyes, invokes in an arcane voice, twelve ancient names.\n", me);
}

tear(object robe, object me){
   robe->remove_object();
   tell_room(EN(me), QCTNAME(me) + " tears apart " + me->query_possessive() + 
      " white robe.\n", me);
   me->catch_msg("You tear apart your white robe as you sound out the ancient names.\n");
}


bye_staff(object staff){
   staff->destroy_staff(staff);
}


echoes(object me){
   tell_room(EN(me), "An eerie darkness gathers from thick clouds of mist that appear from nowhere.\n");
   if(random(10) > 5) tell_room(EN(me), "Voices whisper out of forming clouds in the dark places.\n");
   if(random(10) > 8) tell_room(EN(me), "Someone whispers: Weep for the death of the righteous\n");
   if(random(10) > 6) tell_room(EN(me), "Weeping voices echo from the mysterious mists.\n");
}

chosen(object me){
   
   me->catch_msg("The Twelve appear in a vision before you.\n");
   tell_room(EN(me), QCTNAME(me) + " is overshadowed by a mysterious light and " 
      + me->query_possessive() + " countenance becomes one of dread.\n", me);
   map(users(), mystic);
   set_alarm(2.0, -1.0, "white", me);
   map(users(), evils);
   
}

white(object me){
   tell_room(EN(me), QCTNAME(me) + " turns pale and falls upon the ground, writhing in agony.\n", me);
   me->catch_msg("You fall upon the ground in fear of the dreadful glory of the Ancients.\n");
   me->add_fatigue(-100);
}

