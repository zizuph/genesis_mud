/*********************************************************************
 * - captain.c                                                     - *
 * - shipline Gont-Kabal                                           - *
 * - Candelis                                                      - *
 * - Recoded by Damaris 5/2003                                     - *
 * Ship rerouted to Newbie line , Tapakah, 05/2009                 - *
 *********************************************************************/
#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <money.h>
#include <ss_types.h>
#include <macros.h> 
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit NEWBIE_CAPTAIN;
inherit "/d/Khalakhor/lib/knowledge_base";

public void
create_captain()
{
  ::create_captain();
  set_name("logaan");
  add_name("_logaan_");
  add_name("captain");
  add_name("Leneer");
  set_living_name("logaan");
  set_race_name("human");
  add_adj(({"glaring","suspicious"}));
  set_title("Leneer, the Deadly Corsair");
  set_stats(({150,175,150,125,125,150}));
  set_skill(SS_SWIM,100);
  set_skill(SS_DEFENCE,100);
  set_skill(SS_BLIND_COMBAT,100);
  set_skill(SS_UNARM_COMBAT,100);
  set_skill(SS_AWARENESS,100);
  heal_hp(15000);
  
  seteuid(getuid());
  MONEY_MAKE_GC(random(5) + 3)->move(this_object());
  MONEY_MAKE_CC(random(100) + 100)->move(this_object());
  
  add_prop(OBJ_M_NO_ATTACK,
           "Your futile attempts are thwarted by a mysterious enchantment "+
           "about the captain.\n");
  add_prop(OBJ_M_NO_MAGIC_ATTACK,
           "Your futile attempts are thwarted by a mysterious enchantment "+
           "about the captain.\n");
  
  add_prop(NPC_I_NO_LOOKS, 1);
  
  set_act_time(15);
  add_act("emote gazes out over the water lovingly.");
  add_act("emote smiles admiring at his ship.");
  add_act("emote sighs deeply looking out over the sea.");
  add_act("emote smiles in satisfaction.");
  add_act("say The seas, the seas, they call to me."); 
  add_ask(({"kabal"}),
          "say Kabal port district isn't as busy as it used to be.",1);
  add_ask(({"ocean"}),
      "say The ocean is like a wife, lover, sister, my best friend.",1);
  add_ask(({"route"}),
          "say Sparkle, Gelan Kabal Port District and Gont.",1);
  add_ask(({"port gont","port","gont","town"}),
          "say Gont is an interesting place to visit.",1);
  add_ask(({"candelis","boat","ship"}),
          "say Aye, she's beautiful isn't she? Like me lover she is.",1);
  add_ask("destination","@@query_destination",1);
}
 
