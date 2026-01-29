/*
 * Goblin village elder
 * TAPAKAH 05/2005
 */

#pragma strict_types

#include <ss_types.h>
#include <money.h>
#include <stdproperties.h>
#include <const.h>
#include <macros.h>

#include "/d/Khalakhor/sys/defs.h"

#include "../../daenbraigh.h"
#include "../../village/village.h"
#include "../../faction.h"

inherit "/d/Khalakhor/std/monster";
inherit DAENBRAIGH_NPC;
inherit V_MAGI_CONFUSE;
inherit V_MAGI_COLD;

void equip_me();

void
create_khalakhor_monster()
{
  if(! IS_CLONE)
    return;
  ::create_khalakhor_monster();

  set_name("Aillin");
  add_name(({"aillin","elder","goblin",V_OBJID + "_elder"}));
  set_race_name("goblin");
  set_adj("wize");
  add_adj("powerful");

  set_long("This goblin is the elder of the village of " + VILLAGE_NAME + ". "+
	   "However ugly and repulsive he is, you see an enormous wisdom "    +
	   "behind his eyes and realize the power he wields. All the village "+
	   "inhabitants obey him without hesitation and the garrison leaders "+
	   "are eager to cooperate with him.\n");

  set_gender(G_MALE);

  set_base_stat(SS_STR,100,10);
  set_base_stat(SS_DEX,120,10);
  set_base_stat(SS_CON,180,10);
  set_base_stat(SS_INT,220,10);
  set_base_stat(SS_WIS,190,10);
  set_base_stat(SS_DIS,150,10);
  
  set_skill(SS_UNARM_COMBAT, 60);
  set_skill(SS_DEFENSE, 60);

  set_alignment(0);
  set_faction(FACTION_DAENBRAIGH,FCT_VALUE_LEADER);
  set_alarm(0.5,0.0,equip_me);

  set_chat_time(10);
  add_chat("The garbage is piling upon this village.");
  add_chat("The humans in Port Macdunn are a threat we must eliminate!");
  add_chat("I will get my hands on that courier drunk.");

  set_default_answer("Only wise should know the answer to this.");
  add_ask(({"goblin","goblins","daenbraigh","Daenbraigh"}),
	  "say The goblins shall conquer and rule the world.",
	  1);
  add_ask(({"soldiers","soldier","camp","garrison"}),
	  "say Our military force is strong, but will need more than swords.",
	  1);
  add_ask(({"human","humans","Port Macdunn",
	    "Port macdunn","port macdunn","port Macdunn"}),
	  "say They're our main enemies. After Port Macdunn falls, "+
	  "the battle is decided.",
	  1);
  add_ask(({"elf","elves"}),
	  "say The elves are weak and won't be able to resist us.",
	  1);
  add_ask(({"dwarf","dwarves"}),
	  "say They will live and work for us. Some already do.",
	  1);
  add_ask(({"gnome","gnomes","hobbit","hobbits"}),
	  "say I've never heard of such creatures.",
	  1);
  add_ask(({"garbage","village"}),
	  "say Someone has to collect the garbage in the village. I will "+
	  "reward you if you do so.",
	  1);
  add_ask(({"courier","drunk","drunk courier"}),
	  "say A courier is supposed to run between the village and the "+
	  "Hammerhands. I suspect he is most often in the pub, drinking "+
	  "instead. Prove me he is doing so and you will be rewarded.",
	  1);
  add_ask(({"hammer","hammer hands","hammerhands","Hammerhands"}),
	  "say Hammerhands train our soldiers to be the best warriors on " +
	  "Khalakhor, you may want to visit their headquarters beyond the "+
	  "forest.",
	  1);
}

int
special_attack(object enemy)
{
  int sptype;
  
  if(random(5))
    return 0;

  tell_room(ENV(TO), QCTNAME(TO) + " steps back and raises his hands.\n");
  sptype = random(2);

  switch(sptype)
    {
    case 0:
      write("COLD\n");
      cold_spell(TO,enemy);
      break;
    case 1:
      write("CONFUSE\n");
      confuse_spell(TO,enemy);
      break;
    }
  return 1;
}

void
equip_me()
{
  setuid();
  seteuid(getuid());

  clone_object(V_ROBE)->move(TO);
  command("wear all");
  add_prop(OBJ_M_HAS_MONEY,V_GOBLIN_MON*144);
}

void
init_living()
{
  ::init_living();
  
}
