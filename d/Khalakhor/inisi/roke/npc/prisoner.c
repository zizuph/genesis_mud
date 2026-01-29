/*
 * prisoner.c
 *
 * Used in nyreese/cas_dung1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/monster";

#include "defs.h"
#include <macros.h>

int started;

void meet();
void story(object tp);
void story2(object tp);
void story3(object tp);
void story4(object tp);

int
query_knight_prestige ()
{
  return -1;
}

void
create_monster ()
{
  started = 0;

  set_alignment(199);

  set_name("prisoner");
  set_adj("old");
  add_adj("dying");

  set_long("This is an old dying prisoner. He has obviously been here " +
           "a very long time.\n");

  default_config_npc(13);

  set_race_name("hobbit");

  add_notify_meet_interactive("meet");
}

void
init_living ()
{
  // Trigger the meet function on every command
  add_action("meet", "", 1);
}

int
meet ()
{
  if (!started && ENV(TO)->query_prop(OBJ_I_LIGHT) > 0)
    {
      started = 1;
      set_alarm(2.0, 0.0, &story(TP));
    }
  return 0;
}

void
story (object tp)
{
  command("smile");

  set_alarm(1.0, 0.0, &story2(tp));
}

void
story2 (object tp)
{
  command("say Finally someone that can release me from my captivity.");
  command("whisper " + tp->query_real_name() +
          " I will tell you something...");

  set_alarm(2.0, 0.0, &story3(tp));
}

void
story3 (object tp)
{
  command("whisper " + tp->query_real_name() +
          " Many years ago, I worked for the wizard Kanthrun who" +
          " ruled the castle.");
  command("whisper " + tp->query_real_name() +
          " But one day the evil Refnas turned him into a dragon.");
  command("emote looks very weak.");

  set_alarm(3.0, 0.0, &story4(tp));
}

void
story4 (object tp)
{
  command("whisper " + tp->query_real_name() +
          " Rumours say that Refnas' wand can turn him back...");

  object wounds = clone_object(WOUNDS);
  set_hp(0);
  do_die(wounds);
}
