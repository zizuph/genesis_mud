/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <comb_mag.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TP        this_player()
#define TO        this_object()
#define ETP       environment(TP)
#define ENT environment(TP)
#define EN environment
#define MANA_COST 50
#define SUC_LIM   80

feeling(object who){
   if(living(who)){
      if(who->query_alignment() < -100) set_alarm(4.0, -1.0, "evil", who);
      if(who->query_prop(LIVE_I_UNDEAD)) set_alarm(5.0, -1.0, "undead", who);
      if(who->query_alignment() > 200){
         set_alarm(4.0, -1.0, "good", who);
      }
      else set_alarm(4.0, -1.0, "neutral", who);
   }
}

nomask mixed
cantus(string str)
{
   int i, suc;
   object  *all;
   
   if (NPMAGIC(TP))
      return "Somehow your song fails.\n";
   
   if (TP->query_mana() <= MANA_COST)
      return "You do not have the strength.\n";
   
   suc = random(TP->query_skill(SS_FORM_CONJURATION)) +
   random(TP->query_skill(SS_ELEMENT_LIFE));
   
   if (suc < SUC_LIM) {
      say(QCTNAME(TP) + " whispers a strange song.\n");
      TP->add_mana(-MANA_COST/3);
      return "Your voice reaches out to the Ancients, " +
      "but no contact is made.\n";
   }
   
   say(QCTNAME(TP) + " incants an ancient song, raising " +
      TP->query_possessive() + " hands and looking upwards.\n");
   write("You intone the Song of Antiquity.\n");
   TP->add_mana(-MANA_COST);
   set_alarm(2.0, -1.0, "sounds", TP);
   map(all_inventory(ETP), feeling);
   set_alarm(4.0, -1.0, "visions", TP);
   set_alarm(8.0, -1.0, "reso", TP);
   
   return 1;
}

sounds(object who){
   tell_room(EN(who), "The song of " + QCTNAME(who) + " takes on a life of its own, echoing from the shadows all about, growing and growing!\n", who);
   who->catch_msg("The song begins to grow from the spirit world.\n");
}

visions(object who){
   tell_room(EN(who), "A ghostly winged spirit appears, flying over, echoing the song with a haunting voice.\n");
   if(random(10) > 5) set_alarm(2.0, -1.0, "vision2", who);
}

visions2(object who){
   tell_room(EN(who), "An eerie mist passes through.\n");
}


evil(object who){
   who->catch_msg("Something about this song terrifies you! You feel weak as though you might pass out.\n");
   who->add_fatigue(-20);
   who->add_panic(20);
}

undead(object who){
   if(who->query_prop(LIVE_I_UNDEAD) < random(100) + 50){
      who->catch_msg("A spiritual force tears at your spirit, attempting to cast it into oblivion. Your lifeless state makes you feel as though you may lose your form!\n");
      who->add_fatigue(-30);
      who->add_panic(30);
   }
   who->catch_msg("This song is anethma to your lifeless state.\n");
}

neutral(object who){
   who->catch_msg("Some strange power from the song enters into your spirit, but it quickly leaves you, as though it does not belong. A sense of sorrow overcomes you as it departs.\n");
}


good(object who){
   who->catch_msg("Some spiritual power comes from the song and enters your soul. A sense of warmth and peace pervades you, echoing a belonging to some great virtue.\n");
   who->add_fatigue(20);
   who->add_panic(-20);
   who->heal_hp(20 + TP->query_skill(SS_ELEMENT_LIFE)/2);
   if(MEMBER(who)) set_alarm(1.0, -1.0, "member", who);
}

member(object who){
   who->catch_msg("You feel very close to the Ancients.\n");
}

