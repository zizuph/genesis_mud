//     Igneous'  Laughing gas effect

//     Loosely based on /std/posion_effect.c
//     This is the effect of the gas which is
//     cloned to the player.

//     Copyright (C)  Chad Richardson   March 96

#pragma save_binary

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"

//   Prototypes
void do_laugh();
void set_up_effect();
void timeout();

int          delay_time, laugh_time, effect_time;
object       victim;

void
create_object()
{
   set_name("giggly");
   set_long("Laughing gas effect.\n");
   set_short("giggly");
   set_no_show();
   add_prop(OBJ_I_VALUE, 0);
   add_prop(OBJ_I_VOLUME, 0);
   add_prop(OBJ_I_WEIGHT, 0);
   add_prop(OBJ_M_NO_DROP, "@@no_drop@@");
   add_prop(OBJ_M_NO_GIVE, "Give what to whom?\n");
}

void
start_laughing(object player)
{
   victim = player;
    delay_time = set_alarm(itof(random(16)),0.0,&set_up_effect());
}

void
set_up_effect()
{
   remove_alarm(delay_time);
   victim->catch_msg("You feel the uncontrollable urge to laugh.\n");
   effect_time = set_alarm(itof(120+random(91)),0.0,&timeout());
   laugh_time = set_alarm(1.0,itof(random(16) + 5),&do_laugh());
}

string
no_drop()
{
   return(capitalize(query_verb())+" what?\n");
}

void
timeout()
{
   victim->catch_msg("The uncontrollable urge to laugh has finally ceased.\n");
   remove_alarm(effect_time);
   remove_alarm(laugh_time);
   remove_object();
}

void
do_laugh()
{
   switch(random(6))
   {
      case 0:
      victim->command("$laugh");
      break;
      case 1:
      victim->command("$laugh hys");
      break;
      case 2:
      victim->command("$laugh uncontrol");
      break;
      case 3:
      victim->command("$laugh loudly");
      break;
      case 4:
      victim->command("$chuckle");
      break;
      case 5:
      victim->command("$giggle");
      break;
   }
}
