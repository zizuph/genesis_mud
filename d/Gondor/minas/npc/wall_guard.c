/* This file is /d/Gondor/minas/npc/wall_guard.c     */
/*                                                     */
/* Olorin, July 1993                                   */
/* Increased size and skills, Eowul, April 11th, 2009 */

inherit "/d/Gondor/minas/npc/std_gondor_guard.c";

#include <macros.h>
#include <language.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define WEP_ARRAY1 ({WEP_DIR + "hhalberd", WEP_DIR + "gspear", WEP_DIR + "dlongsword", WEP_DIR+ "gbspear" })
#define WEP_ARRAY2 ({ARM_DIR + "gshield"})
#define ARM_ARRAY1 ({ARM_DIR + "ghelmet"})
#define ARM_ARRAY2 ({ARM_DIR + "gchainmail"})

create_monster()
{
  int rnd;
  if (!IS_CLONE) return;
  seteuid(getuid());
  ::create_monster();
  set_short("tall guard");
  set_pshort("tall guards");
  set_name("guard");
  set_pname("guards");
  set_long(BSN(CAP(LANG_ADDART(implode(query_adjs()," "))) + 
    " man from Lebennin or Lamedon in the " +
    "south of Gondor, with a stern face and dark hair. He is a " +
    "soldier in the Gondorian Army, on duty as a guard. "));

  rnd = random(30);
  default_config_npc(105+rnd/2);
  set_base_stat(SS_STR, 105+rnd);
  set_base_stat(SS_DIS, 165+rnd);
  set_skill(SS_WEP_SWORD,80+rnd/2);
  set_skill(SS_WEP_POLEARM,70+rnd/2);
  set_skill(SS_PARRY,    70+rnd/2);
  set_skill(SS_DEFENCE,  70+rnd/2);
  add_prop(CONT_I_HEIGHT,180+rnd/2);
  add_prop(CONT_I_WEIGHT,75000+rnd*500);
  add_prop(CONT_I_VOLUME,70000+rnd*500);    
  add_prop(LIVE_I_SEE_DARK,0);

  set_chat_time(25+random(15));
  add_chat("All this waiting and idleness makes me weary.");
  add_chat("I wonder, will the Rohirrim come to strengthen us?");
  add_chat("They say women and children will have to be evacuated.");

  set_cchat_time(25+random(10));
  add_cchat("By Gondor! This was not the attack we expected!");
  add_cchat("Where are the archers when we need them?");
  add_cchat("Die, foe! The City can never be taken!");
  add_cchat("The Rohirrim will come to our aid - they must!");
  add_cchat("In the name of the Steward - begone!");

  set_act_time(15+random(15));	
  add_act("sigh");
  add_act("twiddle");
  add_act("stare");
  add_act("tap");

  set_cact_time(2+random(2));
  add_cact("growl");
  add_cact("cry");
  add_cact("scream");
  add_cact("moan");
  add_cact("shout Enemies are attacking! Reinforcements!");
  add_cact("shout Help! Reinforcements!");

  set_hp(query_max_hp());
}

set_arm_arrays()
{
  ::set_arm_arrays();
  wep1 = WEP_ARRAY1;
  wep2 = WEP_ARRAY2;
  arm1 = ARM_ARRAY1;
  arm2 = ARM_ARRAY2;
}

int
query_knight_prestige()
{ return -7; }


