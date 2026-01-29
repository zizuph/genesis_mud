/*
 * bard.c
 *
 * Used in nyreese/cadu_out.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 * Cleaned up even more, synced with the whore by Tapakah, 06/2021.
 */

/* A bard, givin roses to ladies
   Joshua 950128                 */

#pragma strict_types

#include <macros.h>
#include <const.h>

#include "defs.h"

inherit ROKEDIR + "npc/rose-quest";

string job ();

void
create_monster ()
{
  add_name("bard");
  set_adj("smiling");
  add_adj("dreaming");
  set_race_name("human");
  set_short("smiling dreaming bard");

  set_long("He seems detached from the troubles in this world, dreamingly "+
           "playing his songs. He seems particularly inspired by the female "+
           "beauty.\n");
   
  default_config_npc(30);

  // Silly answers written by Damaris
  add_ask("help", "emote exclaims: Help me yes or help me no. One never knows unless you've got toes!", 1); //laugh?
  add_ask("toes", "emote exclaims: Heh you must be dim-witted to ask me thus. You think with help you can be in my trust?", 1); //laugh?
  add_ask("task", "emote exclaims: Oh I've got tasks all the time. But there is never a reason in my rhyme.", 1);
  add_ask("quest", "emote exclaims: Ahh once there was a man who wanted a quest he asked me so many questions I had to put him to rest.", 1);
  add_ask("job", &job());

  set_act_time(10);
  add_act("sing");
  add_act("say Is this the best of all worlds?");
  add_act("say Sometimes I feel like I am nothing more than an object...");
  add_act("smile dreamily");
}

string
job ()
{
  command("emote exclaims: Job ... smob? or corn on the cob.");
  set_alarm(1.0, 0.0, &command("laugh"));
  set_alarm(2.0, 0.0, &command("emote exclaims: Job flob, and you call me a snob."));
  set_alarm(3.0, 0.0, &command("laugh"));
  return "";
}

void
offer_female (object who)
{
  if (!present(who, environment())) return;
  if (!CAN_SEE(this_object(), who)) return;
  command("say to " + OB_NAME(who) + " What wouldn't I give to see you smile?");
}

void
init_living ()
{
  ::init_living();
  if (TP->query_gender() == G_FEMALE)
    set_alarm(2.0, 0.0, &offer_female(TP));
}
