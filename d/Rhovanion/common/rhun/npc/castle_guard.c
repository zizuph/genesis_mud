inherit "/std/monster";

#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"

int armed = 0;

void arm_me()
{
  string wep, arm;

  if(armed) return;
  armed = 1;
  reset_euid();

  wep=ONE_OF_LIST(({"club","axe","sword","pole"}));
  clone_object(WEAPON_DIR+wep+"_med")->move(TO);
  command("wield all");

  clone_object(RHUN_DIR+"npc/chainmail")->move(TO);
  if(random(2))
  {
    arm=ONE_OF_LIST(({"shield","helm"}));
    clone_object(ARMOUR_DIR+arm+"_med")->move(TO);
  }
  command("wear all");
}

void create_monster()
{
    string adj=ONE_OF_LIST(({"ugly","strong","mean","menacing","aggressive",
                             "evil","uncomfortable","alert"}));

    set_alarm(itof(random(10)), 0.0, "arm_me");

    set_race_name("human");
    set_adj(({adj,"easterling","easterling"}));
    set_name(({"easterling","easterling","guard"}));
    set_short(adj+" "+ONE_OF_LIST(({"easterling","easterling"}))+" guard");
    
    set_gender(0);
    set_alignment(-340);
    set_long("This guard is walking the castle halls.  He appears "+
	     "quite strong and well-trained.\n");
	
    add_prop(CONT_I_WEIGHT, 75*1000);
    add_prop(CONT_I_VOLUME, 75*1000);
    add_prop(CONT_I_HEIGHT, 180);
    set_stats(({55, 55, 55, 50, 50, 60}));

    set_skill(SS_UNARM_COMBAT, 36);
    set_skill(SS_DEFENCE, 30);
    set_skill(SS_WEP_SWORD,54);
    set_skill(SS_WEP_AXE,54);
    set_skill(SS_WEP_CLUB,54);
    set_skill(SS_WEP_POLEARM,54);
    set_skill(SS_PARRY, 45);

    set_random_move(4);
    set_restrain_path(RHUN_DIR+"castle");
}

