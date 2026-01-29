/*
 * luder.c
 *
 * Used in nyreese/red_bordell.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 *
 * Modification log:
 *   05/22/17 (Gorboth) - Removed gender-specific quest block.
 *   06/2021 (Tapakah):
 * Reverted Gorboth modification:
 * There's a Bard that works for females. The neuters are served by both.
 * Also did some cleanup
 *
 */

#pragma strict_types

#include <macros.h>
#include <const.h>

#include "defs.h"

inherit ROKEDIR + "npc/rose-quest";


void
create_monster ()
{
  set_race_name("lady");
  set_name("helena");
  add_name("lady");
  set_adj("beautiful");
  add_adj("young");
  set_living_name("helena");
  set_title("the most beautiful one");
  set_short("beautiful young lady");

  /* this monster is named after Gres' commanding officer in the
     Airforce (She is rather cute, but a real bitch.) */

  set_long("This is a beautiful young lady, always prepared to please you.\n");
  add_prop(NPC_I_NO_LOOKS, 1);
  set_gender(G_FEMALE);

  default_config_npc(45);

  ::create_monster();

  add_notify_meet_interactive("met");
}

void
hiho (object tp)
{
  if (tp->query_real_name() == "gresolle") {
    command("hug gresolle");
    command("say Hi my love!");
    command("kiss gresolle");
    command("say how's that dead horse coming along?");
  }
  if (tp->query_gender() == G_MALE)
    set_alarm(2.0, 0.0, &command("smile " + OB_NAME(tp)));
}

void
met ()
{
  set_alarm(1.0, 0.0, &hiho(TP));
}
void
emote_hook (string emote, object actor, string adverb, object *oblist,
            int cmd_attr, int target)
{
  ::emote_hook(emote, actor, adverb, oblist, cmd_attr, target);
  if (actor->query_gender() == query_gender())
    return;
  switch (emote) {
  case "fondle":
    set_alarm(1.0, 0.0, &command("smile " + OB_NAME(actor)));
    break;
  case "kiss":
    set_alarm(1.0, 0.0, &command("love " + OB_NAME(actor)));
    break;
  case "seduce":
  case "love":
    set_alarm(1.0, 0.0, &command("french " + OB_NAME(actor)));
  break;
  case "hug":
    set_alarm(1.0, 0.0, &command("fondle " + OB_NAME(actor)));
    break;
  case "cuddle":
    set_alarm(1.0, 0.0, &command("hug " + OB_NAME(actor)));
    break;
  case "wink":
    set_alarm(1.0, 0.0, &command("wink " + OB_NAME(actor)));
    break;
  case "lick":
    set_alarm(1.0, 0.0, &command("moan"));
    break;
  case "snuggle":
  case "flirt":
    set_alarm(1.0, 0.0, &command("blush"));
    break;
  case "grope":
    set_alarm(1.0, 0.0, &command("groan"));
    break;
  }
}
 
