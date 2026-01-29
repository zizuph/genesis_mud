#pragma save_binary
/* Glindor's original poison file for the blue leaf */

inherit "/std/poison_effect";
#include "/sys/poison_types.h"

create_poison_effect()
{
   ::create_poison_effect();
   
   set_interval(20);
   set_time(200);
   set_poison_type("herb");
   set_strength(1);
   
   set_damage(({POISON_HP,30,POISON_FATIGUE,30}));
   
}

start_poison()
{
   ::start_poison();
   poisonee->set_invis(1);
   poisonee->catch_msg("You are now invisible.\n");
}

timeout()
{
   poisonee->catch_msg("You are visible again.\n");
   poisonee->set_invis(0);
   ::timeout();
}

