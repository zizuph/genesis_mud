/* Tar, Proprietor of the Inn of the Hungry Hungry Halfling */

inherit "/d/Cirath/std/monster.c";
#include "defs.h"

object me=this_object();
void
create_monster()
{
  ::create_monster();
  set_name("tar");
  set_race_name("halfling");
  set_adj("small");
  add_adj("glaring");
  set_title("Tatarminis, proprietor of the Inn of the "+
    "Hungry Hungry Halfling");
  set_long("This halfling, while only knee high on a "+
    "half-giant, looks tougher than iron.  She runs "+
    "this Inn with a brusque efficiency and commanding "+
    "presence.\n"+
    "She has scars on her right cheek, nose and left arm.\n"+
    "Her nose is pierced.\n"+
    "Her hair is long, curly, and uncombed.\n"+
    "She is wielding a bone wrist razor.\n");
  set_gender(1);
  default_config_npc(60);
  add_prop(OBJ_M_NO_ATTACK,"It seems you cannot do that.\n");
  add_prop(OBJ_M_NO_MAGIC_ATTACK,"It seems you cannot do that.\n");
  set_speak("Do you know a good recipe for dwarf meat?");
  set_default_answer("She replies: Just order something!\n");

  set_alignment(0);

  add_act("emote cleans a table.");
  add_act("emote glares at an elf passing by on the street.");
  add_act("emote stares at you.");
  add_act("say Try our stew.");
  add_act("say You want food?");
  add_act("say Roast leg of elf is delicious.");
  add_act("say I need a recipe for dwarf.");
  add_act("say Our stew is always fresh.");
  add_act("emote gives a steaming bowl of soup to a thri-keen.");

  set_act_time(6);

}

