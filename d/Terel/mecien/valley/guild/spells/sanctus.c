/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>


#define TP this_player()
#define TO this_object()
#define EN environment
#define ENV environment
#define PATH "/d/Terel/mecien/valley/guild/spells/"
#define DIS query_stat(SS_DIS)
#define GS query_stat(SS_OCCUP)

try_affect(object who){
   if(living(who)){
      
      if((who->query_alignment() < -100) || who->query_prop(LIVE_I_UNDEAD))
         {
         if(who->query_prop(LIVE_I_UNDEAD)){
            if(random(who->DIS) + random(who->GS) + random(100) < 240){
               set_alarm(2.0, -1.0, "lose_form", who);
            }
         }
         who->catch_msg("Your ears ring with echoing sounds, driving you mad, forcing you to sway about like some wild animal!\n");
         tell_room(ENV(who), QCTNAME(who) + " wretches around, clawing and gnashing, like some maddened animal unable to control itself!\n", who);
  tell_room(EN(who), QCTNAME(who) + " howls out a tortured sound!\n", who);
         who->add_panic(20);
         who->add_fatigue(-100);
         who->add_attack_delay(20, 0);
         return 1;
      }
      
      set_alarm(2.0, -1.0, "feel_stun", who);
   }
}


feel_stun(object who){
   
   who->catch_msg("You feel stunned by some mysterious force passing through you!\n");
}

lose_form(object who){
   
   
   seteuid(getuid());
   if(!living(who)) return;
   if(who->query_prop(LIVE_I_UNDEAD)){
      who->catch_msg("The sacred words strike you like fire in your mind!\n");
      who->heal_hp(-50);
      who->add_panic(100);
      who->add_fatigue(-100);
      tell_room(ENV(who), who->query_name() + " shrieks and cries out in agony.\n", who);
      set_alarm(2.0, -1.0, "feel_decay", who);
      set_alarm(5.0, -1.0, "disintigrate", who);
      return;
   }
}

feel_decay(object who){
   who->catch_msg("You feel your flesh begin to disintigrate!\n");
  tell_room(EN(who), QCTNAME(who) + " wails out a disturbing moan of agony!\n", who);
}



disintigrate(object who){
   
   object home, room, control, dcloud;
   int dur;
   
   if(interactive(who)){
      control = clone_object(PATH + "formless");
      dcloud = clone_object(PATH + "dcloud");
      
      room = clone_object("/d/Terel/mecien/rooms/pit");
      control->set_duration(dur);
      control->set_pit_room(room);
      
      dcloud->set_player_link(who, control);
      return;
   }
   who->catch_msg("You are engulfed in a blaze of white light!\n");
   tell_room(ENV(who), who->query_name() + " is engulfed in a blaze of fiery white light!\n", who);
   who->remove_object();
   return;
   
}


sanctus(){
   int i;
   object *room_list, *dead;
   
   if(TP->query_mana()<250){
      TP->catch_msg("You do not possess the strength.\n");
      return 1;
   }
   if((random(this_player()->query_skill(SS_FORM_CONJURATION))) + 
         random(this_player()->query_skill(SS_ELEMENT_LIFE)) < 90){
      write("You grasp at the untenable words of holiness.\n");
      return 1;
   }
   TP->add_mana(-250);
   TP->catch_msg("You pronounce the most powerful words of holiness.\n");
   tell_room(ENV(TP), TP->query_name() + " raises up " +
      TP->query_possessive() + " hands, standing like a solemn " +
      "majesty and pronounces some unfathomable words!\n", TP);
   map(all_inventory(ENV(TP)), try_affect);
   return 1;
}


