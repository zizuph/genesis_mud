/*
 * butler.c
 *
 * Used in nyreese/cas_c6.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 * Tidied up by Tapakah, 06/2021
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "lib/monster";

#include <ss_types.h>

string *says = ({
  "Please do not disturb my master.",
  "He is very busy, minding his own matters.",
  "I advise you to do the same, heretic!",
  "Watch your steps! Don't step on the leeches!",
});

string
close_door_or_speak ()
{
  if (random(2))
    if (ENV(TO)->query_open()) {
      command("close door");
      return "lock door with key";
    }
    else
      return "emote looks at the leeches.";
  
  return "say " + one_of_list(says);
}

void
create_monster ()
{
  default_config_npc(25);
  set_skill(SS_DEFENCE, 25);
  set_skill(SS_UNARM_COMBAT, 25);
  set_alignment(-200); // Aligns with his master, doesn't he?
  
  set_name("butler");
  set_short("spooky butler");
  set_adj("spooky");
  add_name("human");
  
  set_long("The spooky butler is the servant of the wizard Refnas.\n" +
           "He is taking care of his master's leech farm.\n");
  
  add_act(close_door_or_speak);
}

int
query_knight_prestige ()
{
  return -1;
}
