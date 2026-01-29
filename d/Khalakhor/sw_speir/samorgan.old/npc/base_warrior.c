/* Basic SaMorgan warrior
 * Tapakah 04/2021
 */

#include <ss_types.h>
#include <stdproperties.h>

#include "../defs.h"

inherit KSTDELF;
inherit SAMORGAN_NPC;

#define ID "_sa_morgan_guard"

int level = 0;

public nomask void
set_samorgan_level(int new_level)
{
  level = new_level;
}

public void
init_level ()
{

  default_config_npc(50 + 20*level + random(20));

  foreach (int skill: ({SS_POLEARM, SS_DEFENCE, SS_PARRY, SS_ACROBAT}))
    set_skill(skill, 50 + 10*level);

  foreach (int skill: ({SS_AWARENESS, SS_BLIND_COMBAT, SS_UNARM_COMBAT}))
    set_skill(skill, 30 + 10*level);
  add_prop(LIVE_I_NEVERKNOWN, 1);
  set_alignment(100 + 100*level);

}

public void
arm_me ()
{

  object ob_armour;
  foreach (string armour: ({SM_CHAINMAIL, SM_LEGGINGS, SM_HELMET, SM_SHIELD})) {
    ob_armour = clone_object(armour);
    ob_armour->configure_samorgan_armour(level);
    ob_armour->move(TO);
  }
  object ob_weapon;
  switch (level) {
  case 4:
    ob_weapon = clone_object(SM_SWORD);
  case 3:
    ob_weapon = clone_object(SM_HALBERD);
  case 2:
    ob_weapon = clone_object(SM_SPEAR);
  default:
    ob_weapon = clone_object(SM_DAGGER);
  }
  ob_weapon->configure_samorgan_weapon(level);
  ob_weapon->move(TO);
  command("wield all");
  command("wear all");
  
}

public void
create_khalakhor_elf ()
{

  add_name(ID);
  add_name("guard");
  set_gender(G_MALE);
  init_level();
  arm_me();
}
