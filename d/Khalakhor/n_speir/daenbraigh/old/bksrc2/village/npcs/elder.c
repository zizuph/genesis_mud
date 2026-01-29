/*
 * Goblin village elder
 * TAPAKAH 05/2005
 */

inherit "/d/Khalakhor/std/monster";

#include "../../nspeir.h"
#include "../../village/village.h"
#include "/d/Khalakhor/sys/defs.h";

inherit "../../base";
inherit "../magi/confuse";

#include <ss_types.h>
#include <money.h>
#include <stdproperties.h>
#include <const.h>
#include <macros.h>
#include <wa_types.h>

void equip_me();
void cold_spell(object enemy);
void confuse_spell(object enemy);

void
create_khalakhor_monster()
{
  if(! IS_CLONE)
    return;
  ::create_khalakhor_monster();

  set_name("Aillin");
  set_race_name("goblin");
  set_adj("wize");
  add_adj("powerful");

  set_long(BSN("This goblin is the elder of the village of " + VILLAGENAME + ". "+
	       "However ugly and repulsive he is, you see an enormous wisdom behind "+
	       "his eyes and realize the power he wields. All the village inhabitants "+
	       "obey him without hesitation and the garrison leaders are eager to "+
	       "cooperate with him."));

  set_gender(G_MALE);

  set_base_stat(SS_STR,100,10);
  set_base_stat(SS_DEX,120,10);
  set_base_stat(SS_CON,180,10);
  set_base_stat(SS_INT,220,10);
  set_base_stat(SS_WIS,190,10);
  set_base_stat(SS_DIS,150,10);
  
  set_skill(SS_UNARM_COMBAT, 60);
  set_skill(SS_DEFENSE, 60);

  add_prop(GV_VILLAGER,1);
  set_alignment(VILLAGERALIGN*4);
  set_aggressive("@@check_aggressive");
  set_alarm(0.5,0.0,equip_me);

  set_chat_time(10);
  add_chat("The garbage is piling upon this village.");
  add_chat("The humans in Port Macdunn are a threat we must eliminate!");
  add_chat("I will get my hands on that courier drunk.");

  set_default_answer("Only wise know the answer to this.");
  add_ask(({"goblin","goblins","daenbraigh","Daenbraigh"}),
	  BS(QCTNAME(TO) + " says: The goblins shall conquer and rule the world."));
  add_ask(({"soldiers","soldier","camp","garrison"}),
	  BS(QCTNAME(TO) + " says: Our military force is strong, "+
	     "but will need more than swords."));
  add_ask(({"human","humans","Port Macdunn",
	      "Port macdunn","port macdunn","port Macdunn"}),
	  BS(QCTNAME(TO) + " says: They're our main enemies. "+
	     "After Port Macdunn falls, the battle is decided."));
  add_ask(({"elf","elves"}),
	  BS(QCTNAME(TO) + " says: The elves are weak and " +
	     "won't be able to resist us."));
  add_ask(({"dwarf","dwarves"}),
	  BS(QCTNAME(TO) + " says: They will live and work for us. Some already do."));
  add_ask(({"gnome","gnomes","hobbit","hobbits"}),
	  BS(QCTNAME(TO) + " says: I've never heard of such creatures."));
  add_ask(({"garbage","village"}),
	  BS(QCTNAME(TO) +
	     " says: Someone has to collect the garbage in the village. "+
	     "I will reward you if you do so."));
  add_ask(({"courier","drunk","drunk courier"}),
	  BS(QCTNAME(TO) + " says: A courier is supposed to run between "+
	     "the village and the Hammerhands. I suspect he is most often "+
	     "in the pub, drinking instead. Prove me he is doing so "+
	     "and you will be rewarded."));
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
      cold_spell(enemy);
      break;
    case 1:
      confuse_spell(TO,enemy);
      break;
    }
  return 1;
}
void
cold_spell(object enemy)
{
  int damage;
  if(query_mana() < COLD_MANA)
    return;

  tell_watcher("You see a icy ray striking from the elder.\n",enemy);
  enemy->catch_tell("You see an icy ray striking from the elder towards you.\n");
  if(random(enemy->query_magic_res(MAGIC_I_RES_DEATH) + enemy->query_stat(SS_WIS)) < RESIST_LEVEL) {
    damage = COLD_DAMAGE_BASE + random(COLD_DAMAGE_EXTRA);
    if(enemy->query_race_name() == "elf" ||
       enemy->query_race_name() == "human")
      damage += random(COLD_DAMAGE_BASE);
    enemy->hit_me(damage,MAGIC_DT,TO,-1);
    enemy->catch_tell("You feel the ice piercing your body causing an extreme pain.\n");
    if(enemy->query_hp() <= 0)
      enemy->do_die(TO);
  }
  else
    tell_room("The icy ray dissolves in the air.\n");
  add_mana(-1*COLD_MANA);
}
void
equip_me()
{
  setuid();
  seteuid(getuid());

  clone_object(ROBE)->move(TO);
  command("wear all");
  add_prop(OBJ_M_HAS_MONEY,VILLAGERFIN*144);
}
void
init_living()
{
  ::init_living();
  
}
