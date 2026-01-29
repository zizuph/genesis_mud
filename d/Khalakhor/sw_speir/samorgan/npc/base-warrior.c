/* Basic SaMorgan warrior
 * Tapakah 04-05/2021
 */

#pragma no_clone

#include <ss_types.h>
#include <stdproperties.h>
#include <const.h>

#include "../defs.h"

inherit SAMORGAN_NPC;

static mapping remembered = ([]);
#define ID "_sa_morgan_guard"

int level = 0;

public nomask void
set_samorgan_level (int new_level)
{
  level = new_level;
}

public nomask int
query_samorgan_level ()
{
  return level;
}

public void
init_level ()
{

  default_config_npc(40 + 20*level + random(20));

  foreach (int skill: ({SS_WEP_POLEARM, SS_DEFENCE, SS_PARRY, SS_ACROBAT}))
    set_skill(skill, 45 + 10*level + random(10));

  foreach (int skill: ({SS_AWARENESS, SS_BLIND_COMBAT, SS_UNARM_COMBAT}))
    set_skill(skill, 25 + 10*level + random(10));
  add_prop(LIVE_I_NEVERKNOWN, 1);
  set_alignment(50 + 100*level + random(100));

}

public void
equip_me ()
{

  object ob_armour;
  foreach (string armour: ({
             SM_CHAINMAIL, SM_LEGGINGS, SM_HELMET, SM_SHIELD, SM_COIF
           })) {
    if ((level == SM_SERGEANT_LEVEL && armour == SM_SHIELD) || 
        (level != SM_LIEUTENANT_LEVEL && armour == SM_COIF))
      continue;
    if (present(armour->query_name(), TO))
      continue;
    ob_armour = clone_object(armour);
    ob_armour->configure_samorgan_armour(level);
    ob_armour->move(TO);
  }
  string weapon;
  object ob_weapon;
  
  switch (level) {
  case SM_LIEUTENANT_LEVEL:
    weapon = SM_SWORD;
    set_skill(SS_WEP_SWORD, 50 + 10*level);
    break;
  case SM_SERGEANT_LEVEL:
    weapon = SM_POLEARM;
    break;
  case SM_GUARD_LEVEL:
    weapon = SM_SPEAR;
    break;
  default:
    weapon = SM_DAGGER;
    set_skill(SS_WEP_KNIFE, 50 + 10*level);
  }
  if (! present(weapon->query_name(), TO)) {
    ob_weapon = clone_object(weapon);
    ob_weapon->configure_samorgan_guard_weapon(level);
    ob_weapon->move(TO);
    if (level == SM_LIEUTENANT_LEVEL) {
      command("wear chainmail");
      command("wear helm");
    }
    command("wield all");
    command("wear all");
  }
  environment()->add_team(TO);
}

public int
hook_return_intro (string str)
{
  if (remembered[str] && remembered[str] == "bad") {
    command("nod brief");
    command("say Greetings to you.");
  }
  else {
    command("smile warm");
    command("say Hello, sir, have a nice day.");
  }
  return 1;
}

public void
create_khalakhor_elf ()
{

  add_name(ID);
  add_name("guard");
  set_gender(G_MALE);
  init_level();
  equip_me();
  set_act_time(40);
  add_act("drink all", 1);
  add_act("eat all", 1);
}
