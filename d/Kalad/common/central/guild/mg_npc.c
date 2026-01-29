/*
OBJ:  Standard Merchant Guild NPC
BY:   Sebster
DATE: Aug 28, 1994
PURP: All Merchant Guild members should be inherited from this one,
      so that the player will receive appropriate disadvantages from
      killing the NPC.
*/
inherit "/d/Kalad/std/monster";

#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"

#define A_MERCHANT 0

void
create_monster()
{
  ::create_monster();
  add_chat("I am a member of the Merchant Guild!");
  add_cchat("You will live to regret the day you killed a Merchant!");
}

public void
do_die(object killer)
{
  if (interactive(killer))
  {
    string pl_name = killer->query_real_name();
    CENTRAL(guild/mg_kills)->inc_kills(pl_name, A_MERCHANT);
  }
  command("say The Merchant Guild will punish you for this!");
  ::do_die(killer);
}
