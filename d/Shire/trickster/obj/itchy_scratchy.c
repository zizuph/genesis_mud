
//     Igneous' Itching powder effect

//     Loosely based on /std/poison_effect.c
//     Causes a player to scratch themselves uncontrollably
//     To activate the itch use this bit of code:
//     itch = clone_object("this file");
//     itch->move(living_we_want_to_itch);
//     itch->start_itching(living_we_want_to_itch);

//     Copyright (C)  Chad Richardson    Feb. 1996

#pragma save_binary

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"

//    Prototypes
void set_up_effect();
void timeout();
void do_scratch();

int          delay_time, itchy_time, scratchy_time;
object       victim;

void
create_object()
{
   set_name("itchy");
   set_long("itching powder\n");
   set_short("itchy");
   set_no_show();
   add_prop(OBJ_I_VALUE, 0);
   add_prop(OBJ_I_VOLUME, 0);
   add_prop(OBJ_I_WEIGHT, 0);
   add_prop(OBJ_M_NO_DROP, "@@no_drop@@");
   add_prop(OBJ_M_NO_GIVE, "Give what to whom?\n");
}

void
start_itching(object player)
{
   victim = player;
   delay_time = set_alarm(itof(10 + random(20)),0.0,&set_up_effect());
}

void
set_up_effect()
{
   remove_alarm(delay_time);
   victim->catch_msg("You feel itchy all over!!!\n");
   itchy_time = set_alarm(itof(180 + random(91)),0.0,&timeout());
   scratchy_time = set_alarm(1.0,12.0,&do_scratch());
}

string
no_drop()
{
   return(capitalize(query_verb())+" what?\n");
}

void
timeout()
{
   victim->catch_msg("The annoying itch has finally gone away.\n");
   remove_alarm(itchy_time);
   remove_alarm(scratchy_time);
   remove_object();
}

void
do_scratch()
{
   switch(random(6))
   {
      case 0:
      victim->command("$scratch head");
      break;
      case 1:
      victim->command("$scratch chin");
      break;
      case 2:
      victim->command("$scratch back");
      break;
      case 3:
      victim->command("$scratch behind");
      break;
      case 4:
      victim->command("$scratch nose");
      break;
      case 5:
      victim->command("$grumble");
      break;
   }
}
