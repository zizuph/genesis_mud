inherit "/std/monster";

#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"

int armed;

void arm_me()
{
  if(armed) return;
  armed = 1;
  reset_euid();
  clone_object(WEAPON_DIR+"knife_med")->move(TO,1);
  command("wield all");
}

void create_monster()
{

  set_alarm(5.0,0.0,"arm_me");

  set_race_name("human");
  set_adj("town");
  set_name("mayor");
  set_long("This is the mayor of the town.  He's a rather fat man"
          +" dressed in moderately-fine clothes, considering the"
          +" area he lives in.  He doesn't look like he'd give anyone"
          +" any hassle.\n");
  add_prop(CONT_I_WEIGHT, 77*1000);
  add_prop(CONT_I_VOLUME, 77*1000);
  add_prop(CONT_I_HEIGHT, 173);
  set_stats(({48,40,50,50,50,55}));
  set_skill(SS_WEP_KNIFE, 30);
  set_alignment(120);

  set_chat_time(5);
  add_chat("Welcome to our little town!");
  add_chat("We don't have much to offer tourists or visitors.");
  add_chat("Many people have fled the area because of the Easterling warriors.");
}
