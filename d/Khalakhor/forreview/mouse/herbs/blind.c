/* blind object for use in herb, coded by Elizabeth Cook/Mouse, October 1996 */
inherit "/std/poison_effect";
#include <poison_types.h>
#include <stdproperties.h>
#include <macros.h>


void create_poison_effect() 
{
     set_strength(70);
     set_poison_type("blindness");
     set_silent(2);
     set_time(900);
     set_interval(0);
     set_damage( ({ POISON_FATIGUE, 0}) ); 
}

void remove_object()
{
     int x;
     if(poisonee)
     {
         x = poisonee->query_prop(LIVE_I_SEE_DARK);
         if(x==-40)
            poisonee->remove_prop(LIVE_I_SEE_DARK);
         else
            poisonee->add_prop(LIVE_I_SEE_DARK,x+40);
         poisonee->catch_msg("Your vision returns to normal.\n");
         tell_room(environment(poisonee),QCTNAME(poisonee)+" no "+
             "longer stumbles around blindly.\n",poisonee);   
     }
     ::remove_object();
}


void start_poison()
{
     int x;
     ::start_poison();
     x = poisonee->query_prop(LIVE_I_SEE_DARK);
     poisonee->add_prop(LIVE_I_SEE_DARK,x-40);
     tell_room(environment(poisonee),QCTNAME(poisonee)+" is blinded!\n",
           poisonee);
     poisonee->catch_msg("You begin to feel dizzy and your body tingles. "+
          "Suddenly everything goes black! You are blinded!\n");
}


