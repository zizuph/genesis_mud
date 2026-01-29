 // "Potion"        (/d/Avenir/common/port/obj/potion.c)
 // creator(s):   Glinda june -95
 // last update:
 // purpose:      One of the treasures one might find if one kill the
 //               octopus in the shipwreck.
 // note:
 // bug(s):
 // to-do:

inherit "/std/poison_effect";

#include "/d/Avenir/common/common.h"
#include <poison_types.h>

int counter;
object paralyze;

create_poison_effect()
{
   set_interval(20);
   set_time(1200);
   set_damage(({ POISON_USER_DEF, 100 }));
   set_strength(50);
   set_poison_type("standard");
   set_silent(2);   //no std messages.
   counter=0;
}

void
special_damage(int damage)
{
   if(counter>=9)
      counter = 0;
   switch( counter )
   {
      case 0:

         poisonee->add_mana(65);
         poisonee->heal_hp(-200-random(300));
         poisonee->add_fatigue(-70 -random(70));
         poisonee->catch_msg("A horrible pain explodes in your head. You " +
             "pass out.\n");
         tell_room( ENV(poisonee), QCTNAME(poisonee) + " falls to the " +
             "ground writhing in pain, and passes out.\n", poisonee);
       setuid(); seteuid(getuid());
         paralyze = clone_object("std/paralyze");
         paralyze->set_fail_message("You cannot do that. You are unconcious.\n");
         paralyze->set_stop_verb();
         paralyze->set_stop_msg("You wake up aching all over.\n");
         paralyze->set_stop_object(TO);
         paralyze->move(poisonee);
         poisonee->add_prop(LIVE_S_EXTRA_SHORT, 
            " is lying unconscious on the ground");
         if(poisonee->query_hp() <=0)
            poisonee->do_die();
         break;

      case 1:

         poisonee->catch_msg("You fall into a condition of hallucination. " +
             "Your brain seems to be glowing, and you can see your body " +
             "writhing in pain, but you cannot feel a thing. You seem to " +
             "have separated with your body!\n");
         tell_room( ENV(poisonee), QCTNAME(poisonee) +
             " writhes in pain.\n", poisonee);
         break;

      case 2:

         poisonee->catch_msg("You seemingly flow back into your body." +
             " You wake up aching all over.\n");
         poisonee->remove_prop(LIVE_S_EXTRA_SHORT);
         tell_room( ENV(poisonee), QCTNAME(poisonee) + " seems " +
             "to regain senses.\n", poisonee);
         paralyze->stop_paralyze();
         break;
      case 3: break;
      case 4: break;
      case 5: break;
      case 6: break;
      case 7: break;
      case 8: break;
      case 9: break;
   }
   counter ++;
}


timeout()
{
   if(paralyze)
   {
         poisonee->remove_prop(LIVE_S_EXTRA_SHORT);
      paralyze->stop_paralyze();
   }
   ::timeout();
}
