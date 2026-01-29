#pragma save_binary

inherit "/std/monster";

#include "/d/Roke/common/defs.h"
#include "/d/Roke/common/qbits.h"
#include <macros.h>
#include <ss_types.h>

create_monster()
{
  set_name("wizard");
  set_adj("evil");
  set_long("This is the evil wizard Refnas who was turned into a dragon by the good wizard in the castle.\n");
  
  default_config_npc(75);
  set_skill(SS_UNARM_COMBAT,100);
  set_skill(SS_DEFENCE,100);

  set_alignment(-300);
}
viska(string s)
{
  command("whisper "+TP->query_real_name()+" "+s);
}

reward(object tp)
{
  set_this_player(tp);

  if(QDONE(GROUP1,BLUEDRAGON))
    {
      TP->catch_msg("The wizard says: It is really fun to spoil the quest for others, right?\n");
      command("kick "+TP->query_real_name());
      command("emote disappears in a puff of smoke.");
      remove_object();
      return;
    }

  QSET(GROUP1,BLUEDRAGON);
  QLOG("blue dragon");
  
  TP->add_exp(2000,0);

  viska("Thank you! I've been a prisoner here since");
  viska("Krfsm threw me out of the castle.");
  viska("Now I am free to haunt the locals again!");
  viska("You will be handsomly rewarded!");

  TP->catch_msg("You feel more experienced!\n");

  command("emote disappears in a puff of smoke.");
  remove_object();
}
