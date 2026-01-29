/* ctower/npc/knight.c is cloned by ctower/?
 */
inherit "/std/monster";
inherit "/std/act/action";
inherit "/std/act/chat";
 
#include <ss_types.h>
#include "../ctower.h"
#include "/d/Emerald/defs.h"
 
void arm_me();

void
create_monster()
{
  set_name("knight");
  set_race_name("human");
  set_adj("worthy");
  set_short("worthy knight");
  set_long( "The knight looks to be extremely powerful "+
      "and seems to be here of his own free will.\n" );

  add_prop(NPC_M_NO_ACCEPT_GIVE, 1);
 
  set_stats(({ 100, 100, 100,  75,  75, 100 }));
  set_skill(SS_WEP_SWORD, 100);
  set_skill(SS_PARRY, 100);
  set_skill(SS_DEFENCE, 100);

  set_alignment(300);
 
  set_all_hitloc_unarmed(10+random(10));

  refresh_mobile();
 
  set_chat_time(7);
  add_chat("Best of luck!");
  add_chat( "You aren't gonna finish the quest "+
      "standing around here all day!\n" );
  add_chat("I can be of no further help to you.");
 
  set_cchat_time(3);
  add_cchat("There was no need to fight me.");
  add_cchat("Leave now!  I will kill you if you remain!");
 
  set_act_time(5);
  add_act("bow all");
  add_act("smile all");
  add_act("ponder the situation");

  set_alarm(1.0, 0.0, arm_me);
}
 
arm_me()
{
  seteuid(getuid(this_object()));
 
  clone_object(CTOWER_ARM + "phelm")->move(TO, 1);
  clone_object(CTOWER_ARM + "pmail")->move(TO, 1);
  clone_object(CTOWER_ARM + "shield")->move(TO, 1);
  command("wear all");

  clone_object(CTOWER_WEP + "hsword")->move(TO, 1);
  command("wield sword");
}
