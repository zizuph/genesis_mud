/*
 * Any poor girl in Sa Morgan
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
  add_name("girl");
  set_gender(G_FEMALE);
  set_adj(({"fair", "skinny"}));
  set_short("fair skinny girl");
  set_long("This girl is a typical citizen of Sa Morgan. She's an elf, with "+
           "fair complexion and pale face. Her eyes are almond shaped and her "+
           "hair is black and worn in a braid. She seems to be both excited "+
           "and worried at the same time.\n");
  default_config_npc(20);
  set_default_answer("say I would not know anything about it.", 1);
  add_ask(({"quest", "help", "task", "job"}),
            "say I think Lynet could use some help", 1);
  add_act("emote tidies the things around the room.");
  add_act("emote looks at the birds outside the window.");
  set_act_time(10);
  equipment = ({ ARM + "girl-shoes", ARM + "girl-dress", ARM + "girl-apron" });
}
