/* This file is /d/Gondor/minas/npc/wall_guard.c       */
/*                                                     */
/* Olorin, July 1993                                   */
/* Updated to use bows - Rohim 2002                    */
/* Increased size and skills, Eowul, April 11th, 2009 */

inherit "/d/Gondor/minas/npc/std_gondor_guard.c";

#include <macros.h>
#include <language.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define WEP_ARRAY1 ({ITH_DIR + "obj/bow"})
#define ARM_ARRAY1 ({ARM_DIR + "gchainmail"})

public void attack_ranged(object *enemies, object room, string location);

create_monster()
{
  int rnd;
  if (!IS_CLONE) return;
  seteuid(getuid());
  ::create_monster();
  set_short("tall archer");
  set_pshort("tall archers");
  set_name("archer");
  set_pname("archers");
  set_long(BSN(CAP(LANG_ADDART(implode(query_adjs()," "))) + 
    " man from Lossarnach or Tolfalas in the " +
    "south of Gondor, with a stern face and dark hair. He is an " +
    "archer in the Gondorian Army, on duty as a guard. "));

  rnd = random(30);
  default_config_npc(105 + rnd / 2);
  set_base_stat(SS_STR, 105 + rnd);
  set_base_stat(SS_DEX, 135 + rnd);  
  set_base_stat(SS_DIS, 135 + rnd);
  set_skill(SS_WEP_SWORD, 75 + rnd / 2);
  set_skill(SS_WEP_POLEARM, 70 + rnd / 2);
  set_skill(SS_WEP_MISSILE, 90);  
  set_skill(SS_PARRY,    70 + rnd / 2);
  set_skill(SS_DEFENCE,  70 + rnd / 2);
  add_prop(CONT_I_HEIGHT, 180 + rnd / 2);
  add_prop(CONT_I_WEIGHT, 65000 + rnd * 500);
  add_prop(CONT_I_VOLUME, 65000 + rnd * 500);    
  add_prop(LIVE_I_SEE_DARK, 0);

  set_chat_time(25 + random(25));
  add_chat("All this waiting and idleness makes me weary.");
  add_chat("I wonder, will the Rohirrim come to strengthen us?");
  add_chat("They say women and children will have to be evacuated.");
  add_chat("Being an archer has its advantages.");
  add_chat("At least we don't have to enter close combat.");

  set_cchat_time(5 + random(10));
  add_cchat("By Gondor! This was not the attack we expected!");
  add_cchat("Where are the warriors when we need them?");
  add_cchat("We are not supposed to enter close combat!");
  add_cchat("Die, foe! The City can never be taken!");
  add_cchat("The Rohirrim will come to our aid - they must!");
  add_cchat("In the name of the Steward - begone!");

  set_act_time(15 + random(15));	
  add_act("sigh");
  add_act("twiddle");
  add_act("stare");
  add_act("tap");

  set_cact_time(2 + random(2));
  add_cact("growl");
  add_cact("cry");
  add_cact("scream");
  add_cact("moan");
  add_cact("shout Enemies are attacking! Reinforcements!");
  add_cact("shout Help! Reinforcements!");

  clone_object(WEP_DIR + "dlongsword")->move(TO, 1);
  clone_object(ARM_DIR + "gshield")->move(TO, 1);
  clone_object(ITH_DIR + "obj/quiver")->move(TO, 1);
  set_hp(query_max_hp());
}

void
set_arm_arrays()
{
  ::set_arm_arrays();
  wep1 = WEP_ARRAY1;
  arm1 = ARM_ARRAY1;
}

void
change_to_sword()
{
    command("unwield bow");
    command("wield sword");
    command("wear shield");    
}

void
change_to_bow()
{
    if (!query_attack())
    {
	command("unwield sword");
	command("remove shield");
	command("wield bow");
    }
    else
    {
	set_alarm(120.0, 0.0, &change_to_bow());	
    }
}

public void
attacked_by(object enemy)
{
    ::attacked_by(enemy);
    change_to_sword();
    set_alarm(120.0, 0.0, &change_to_bow());
}

public void
attack_ranged_enemies(object *enemies, object room, string location)
{


    if (!query_attack())
    {
	switch(random(5))
	{
	case 0:
	    command("shout Enemies at the gate!");
	case 1:
	    command("emote stretches and picks up his bow.");
	case 2:
	    command("emote silently prepares for battle.");
	}
	attack_ranged(enemies, room, location);
    }
}

public void
attack_ranged(object *enemies, object room, string location)
{
    int size;
    object target;
    string description;
    
    if (!query_attack())
    {
	if (query_weapon(W_BOTH)->query_wt() != W_MISSILE)
	{
	    change_to_bow();
	}
    }
    else
    {
	return;
    }
    
    enemies = filter(enemies, &operator(==)(room) @ &environment());
    size = sizeof(enemies);

    if (size)
    {
	target = enemies[random(size)];
	description = implode(target->query_adjs(), " ") + " " +
	              target->query_race_name();	
	command("shoot " + description + " " + location);
	
	set_alarm(10.0 + itof(random(2)), 0.0,
		  &attack_ranged(enemies, room, location));
    }
}
