//      Igneous' sneeze powder effect

//      Loosely based on /std/poison_effect.c
//      Causes a player to sneeze uncontrolably
//      To start the effect use this bit of code:
//      sneezy = clone_object("dir where this file is found");
//      sneezy->move(living_we_want_to_sneeze);
//      sneezy->start_sneezing(living_we_want_to_sneeze);

//       Copyright  Chad Richardson  Feb 1996

#pragma save_binary

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"

//    Prototypes
void set_up_effect();
void do_sneeze();
void timeout();

int           delay_time, effect_time, sneezy_time;
object        victim;

void
create_object()
{
   set_name("sneezy");
   set_long("sneezing powder effect\n");
   set_short("sneezy");
   set_no_show();
   add_prop(OBJ_I_VALUE, 0);
   add_prop(OBJ_I_VOLUME, 0);
   add_prop(OBJ_I_WEIGHT, 0);
   add_prop(OBJ_M_NO_GIVE, "Give what to whom?\n");
   add_prop(OBJ_M_NO_DROP, "@@no_drop@@");
}


void
start_sneezing(object player)
{
   victim = player;
   delay_time = set_alarm(itof(1 + random(5)),0.0,&set_up_effect());
}

void
set_up_effect()
{
   remove_alarm(delay_time);
   victim->catch_msg("You feel a funny twitch in your nose!!\n");
   effect_time = set_alarm(itof(120 + random(91)),0.0,&timeout());
   sneezy_time = set_alarm(1.0,10.0,&do_sneeze());
}

string
no_drop()
{
   return(capitalize(query_verb())+" what?\n");
}

void
timeout()
{
   victim->catch_msg("Your sinuses finally clear up and you cease to sneeze.\n");
   remove_alarm(effect_time);
   remove_alarm(sneezy_time);
   remove_object();
}

void
do_sneeze()
{
   switch(random(6))
   {
      case 0:
      victim->catch_msg("You sneeze violently. Gezundheit!\n");
      tell_room(ENV(ENV(TO)), QCTNAME(victim) + " sneezes violently.\n", victim);
      break;
      case 1:
      victim->catch_msg("You sneeze uncontrollably. Gezundheit!\n");
      tell_room(ENV(ENV(TO)), QCTNAME(victim) + " sneezes uncontrollably.\n", victim);
      break;
      case 2:
      victim->catch_msg("You sneeze softly. Gezundheit!\n");
      tell_room(ENV(ENV(TO)), QCTNAME(victim) + " sneezes softly.\n", victim);
      break;
      case 3:
      victim->catch_msg("You sneeze loudly. Gezundheit!\n");
      tell_room(ENV(ENV(TO)),QCTNAME(victim)+" sneezes loudly.\n", victim);
      break;
      case 4:
      victim->catch_msg("Your nose starts running somewhat.\n");
      tell_room(ENV(ENV(TO)), QCTNAME(victim) + "'s nose starts to run somewhat.\n", victim);
      break;
      case 5:
      victim->catch_msg("You sniff pitifully.\n");
      tell_room(ENV(ENV(TO)), QCTNAME(victim) + " sniffs pitifully.\n",victim);
      break;
   }
}
