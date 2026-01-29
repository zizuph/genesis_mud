//     Igneous' stinky effect

//     Loosely based on /std/poison_effect.c
//     Causes a player to smell real bad and causes
//     other players in the environment to react to 
//     the horrible smell.
//     To start this effect use this bit of code.
//     stink = clone_object("dir where this file is found");
//     stink->move(living_we_want_to_stink);
//     stink->start_stinking(living_we_want_to_stink);

//     Copyright (C)  Chad Richardson    March 96

#pragma save_binary

inherit "/std/object";

#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"

//   Prototypes
void set_up_effect();
void timeout();
void do_smell();

int          delay_time, stink_time, smelly_time;
object       victim;

void
create_object()
{
   set_name("stinky");
   set_long("Stink_effect.\n");
   set_short("stinky");
   set_no_show();
   add_prop(OBJ_I_VALUE, 0);
   add_prop(OBJ_I_VOLUME, 0);
   add_prop(OBJ_I_WEIGHT, 0);
   add_prop(OBJ_M_NO_DROP, "@@no_drop@@");
   add_prop(OBJ_M_NO_GIVE, "Give what to whom?\n");
}

void
start_stinking(object player)
{
   victim = player;
   delay_time = set_alarm(itof(2 + random(4)),0.0,&set_up_effect());
}

void
set_up_effect()
{
   remove_alarm(delay_time);
   victim->catch_msg("You REALLY stink!\n");
   tell_room(ENV(ENV(TO)), QCTNAME(victim)+ " starts to eminate " +
      "a horrible odor!!\n",victim);
   stink_time = set_alarm(itof(120 + random(60)),0.0,&timeout());
   smelly_time = set_alarm(1.0,15.0,&do_smell());
}

string
no_drop()
{
   return(capitalize(query_verb())+" what?\n");
}

void
timeout()
{
   victim->catch_msg("Whew...  that horrible smell has finally gone away.\n");
   tell_room(ENV(ENV(TO)), QCTNAME(victim)+ " finally smells " +
      "bearable again.\n",victim);
   remove_alarm(stink_time);
   remove_alarm(smelly_time);
   remove_object();
}

void
smell_reaction(object player)
{
   switch(random(10))
   {
      case 0:
      player->catch_msg("The horrid smell coming from "+QTNAME(victim)+" makes "+
         "you want to throw up.\n");
      player->command("$gag");
      break;
      case 1:
      player->catch_msg("The stench coming from "+QTNAME(victim)+" causes "+
         "you to lose your lunch!\n");
      player->command("$puke");
      break;
      case 2:
      player->catch_msg("You wish you were upwind from "+QTNAME(victim)+
         ", as you get a wiff of "+HIS_HER(victim)+" stinky odor.\n");
      player->command("$cough");
      break;
      case 3:
      player->catch_msg(QCTNAME(victim)+" smells so bad, you kick "+
         HIM_HER(victim)+" in hopes that "+HE_SHE(victim)+" will leave.\n");
      player->command("$kick " + victim->query_real_name());
      break;
      case 4:
      player->catch_msg("The putrid smell coming from "+QTNAME(victim)+
         " causes you to choke on something.\n");
      player->command("$choke");
      break;
      default:
      break;    /* So that this effect isn't too annoying */
   }
}

void
do_smell()
{
   object *oblist;
   int    i;
   
   oblist = ({});
   oblist = FILTER_LIVE(all_inventory(ENV(ENV(TO)))) - ({victim});
   if (!sizeof(oblist))
      return;
   tell_room(ENV(ENV(TO)), "A putrid smell assults your nose!\n",victim);
   for (i = 0; i < sizeof(oblist); i++)
   {
      smell_reaction(oblist[i]);
   }
}
