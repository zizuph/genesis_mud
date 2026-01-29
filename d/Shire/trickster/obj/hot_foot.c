#pragma save_binary

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"

#define I_HAVE_A_TRICKSTER_HOTFOOT  "_i_have_a_trickster_hotfoot"

//   Prototypes
void do_pain();
void set_up_effect();
void timeout();

int          delay_time, pain_time, effect_time;
object       victim;

void
create_object()
{
   set_name("_trickster_hot_foot_");
   set_long("The Trickster's hot foot\n");
   set_short("hot foot");
   set_no_show();
   add_prop(OBJ_I_VALUE, 0);
   add_prop(OBJ_I_VOLUME, 0);
   add_prop(OBJ_I_WEIGHT, 0);
   add_prop(OBJ_M_NO_DROP, "@@no_drop@@");
   add_prop(OBJ_M_NO_GIVE, "Give what to whom?\n");
}

void
start_hot_foot(object player)
{
   victim = player;
   delay_time = set_alarm(itof(random(6)),0.0,&set_up_effect());
}

void
set_up_effect()
{
   remove_alarm(delay_time);
   victim->command("$jump");
   victim->catch_msg("You feel an instense burning sensation on your foot!!\n");
   tell_room(ENV(ENV(TO)),QCTNAME(victim)+"'s foot is suddenly engulfed in flames!\n",victim);
   effect_time = set_alarm(itof(15+random(16)),0.0,&timeout());
   pain_time = set_alarm(1.0,itof(random(5) + 3),&do_pain());
   victim->add_prop(LIVE_S_EXTRA_SHORT," is running around with "+HIS_HER(victim)+" foot on fire");
}

string
no_drop()
{
   return(capitalize(query_verb())+" what?\n");
}

void
init()
{
   ::init();
   add_action("extinguish","extinguish");
}

void
timeout()
{
   victim->catch_msg("The flames on your foot has finaly burnt away.\n");
   tell_room(ENV(ENV(TO)),"The flames on "+QTNAME(victim)+"'s foot have finally gone out.\n",victim);
   remove_alarm(effect_time);
   remove_alarm(pain_time);
   victim->remove_prop(I_HAVE_A_TRICKSTER_HOTFOOT);
   victim->remove_prop(LIVE_S_EXTRA_SHORT);
   remove_object();
}

void
do_pain()
{
   switch(random(6))
   {
      case 0:
      victim->command("$sweat");
      break;
      case 1:
      victim->command("$wail");
      break;
      case 2:
      victim->command("$wince");
      break;
      case 3:
      victim->command("$scream");
      break;
      case 4:
      victim->command("$jump painfully");
      break;
      case 5:
      victim->catch_msg("You start to hop madly around the room, fanning your "+
         "foot in hopes that the flames will go out.\n");
      tell_room(ENV(ENV(TO)),QCTNAME(victim)+" hops madly around the room "+
         "fanning "+HIS_HER(victim)+" foot, in hopes the flames will go out.\n",
         victim);
      break;
   }
}

int
extinguish(string str)
{
   if (!str)
      {
      notify_fail("Extinguish what?\n");
      return 0;
   }
   
   if (str == "foot" || str == "hotfoot" || str == "my foot")
      {
      victim->catch_msg("You manage to extinguish the fire "+
         "which was burning on your foot.\n");
      say(QCTNAME(victim)+" manages to extinguish the "+
         "flames which were buring on "+HIS_HER(victim)+" foot.\n",victim);
      remove_alarm(effect_time);
      remove_alarm(pain_time);
      victim->remove_prop(I_HAVE_A_TRICKSTER_HOTFOOT);
      victim->remove_prop(LIVE_S_EXTRA_SHORT);
      remove_object();
      return 1;
   }
   return 0;
}
