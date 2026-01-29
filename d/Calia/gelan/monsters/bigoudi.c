
/*
   Bigoudi Angora, the hairdresser in the town Gelan.
   Coder: Maniac

   Revision history:
   31/5/96   trigs taken out        Maniac
*/



#pragma save_binary

inherit "/std/monster";
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "monster.h"
inherit STD_AIDED;
#include HAUNT_CODE

void
create_monster() 
{
  if (!IS_CLONE)
    return;
  set_name("bigoudi");
  add_name("owner");
  add_name("hairdresser");
  add_name("shopkeeper");
  set_race_name("elf");
  set_adj(({"willowy","effeminate"}));
  set_title("Angora the Hairdresser");
  set_long("Bigoudi Angora is the hairdresser here in Gelan, " +
           "great-grandson of the famous Bobby-pin Angora, inventor of " +
           "the 'Blaze-Away' haircut (don't ask). He seems to be " +
           "somewhat effeminate in his gestures and demeanour, and " + 
           "at the same time quite talkative and friendly.\n");
  default_config_npc(60);
  set_hp(5000);
  set_skill(SS_UNARM_COMBAT, random(20) + 35);
  set_skill(SS_DEFENCE, random(10) + 40);
  set_skill(SS_AWARENESS, random(10) + 50);
  set_alignment(50 + random(100));
  set_act_time(15);
  add_act("emote toys with some scissors."); 
  add_act("emote sweeps up some hair from the floor into a dust pan."); 
  add_act("emote smiles professionally.");
  add_act("emote whistles sentimentally."); 
  add_act("say I cut the hair of everyone in Gelan who doesn't cut their " +
           "own. Work that one out!");
  add_act("say Like a haircut? I'm good at what I do you know!");
  add_cact("Those big guards will save me!");
  add_cact("Didn't you like your haircut?!");
  add_cact("Horrid ruffians!");
  add_cact("Bet you think you're so macho eh?!");
}


void
emote_hook(string emote, object actor, string adverb)
{
    if ((emote == "bow") || (emote == "curtsey"))
        set_alarm(1.0, 0.0, &command("bow " + actor->query_real_name()));
}

