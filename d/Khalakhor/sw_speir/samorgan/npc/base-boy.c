/*
 * Any poor boy in Sa Morgan
 * Tapakah, 05/2021
 */

#pragma no_clone
#pragma strict_types

#include <const.h>

#include "../defs.h"

inherit SM_ELF;

public void
create_khalakhor_elf ()
{
  add_name("boy");
  set_gender(G_MALE);
  set_adj(({"lanky", "pale"}));
  set_short("lanky pale boy");
  set_long("This boy is a typical citizen of Sa Morgan. He's an elf, with "+
           "fair complexion and pale face. His limbs are long, seemingly a "+
           "bit too long, however his movements are graceful. He seems to "+
           "get a dreamy look on his face from time to time.\n");
  set_stats(({25,25,25,15,15,15}), 10);
  set_default_answer("say That does not sound interesting to talk about it.", 1);
  add_ask(({"quest", "help", "task", "job"}),
          "say I think Fearghal could use some help.", 1);
  add_act("emote twirls the tools from the workbench in his hands.");
  add_act("emote stares dreamingly through the window.");
  set_act_time(10);
  equipment = ({ ARM + "boy-shoes", ARM + "boy-breeches", ARM + "boy-shirt" });
}
