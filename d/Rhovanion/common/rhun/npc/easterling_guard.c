inherit "/std/monster";

#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"

int armed;

void arm_me()
{
  object obj;
  string wep,arm;

  if(armed) return;
  armed=1;

  wep=ONE_OF_LIST(({"club","club","club","axe","axe","sword","pole"}));
  arm=ONE_OF_LIST(({"shield","helm"}));

  obj=clone_object(WEAPON_DIR+wep+"_med");
  obj->move(TO);
  command("wield all");

  obj=clone_object(RHUN_DIR+"npc/chainmail");
  obj->move(TO);
  if(random(2))
  {
    obj=clone_object(ARMOUR_DIR+arm+"_low");
    obj->move(TO);
  }
  command("wear all");
}

void create_monster()
{
    reset_euid();
    set_alarm(1.0, 0.0 , "arm_me");

    set_race_name("human");
    set_name(({"Easterling","easterling","soldier","guard"}));
    set_adj("easterling");
    set_short("easterling guard");
    add_name("_easterling_guard");
    
    set_gender(0);
    set_alignment(-340);
    set_long("This is a Easterling soldier on guard-duty.  He seems "+
	"quite strong and well-trained.\n");
	
    add_prop(CONT_I_WEIGHT, 75*1000);
    add_prop(CONT_I_VOLUME, 75*1000);
    add_prop(CONT_I_HEIGHT, 180);
    set_stats(({55, 55, 55, 50, 50, 60}));

    set_skill(SS_UNARM_COMBAT, 36);
    set_skill(SS_DEFENCE, 30);
    set_skill(SS_WEP_CLUB,54);
    set_skill(SS_WEP_SWORD,54);
    set_skill(SS_WEP_AXE,54);
    set_skill(SS_WEP_POLEARM,54);
    set_skill(SS_PARRY, 45);

    set_chat_time(5);
    add_chat("What are you doing here?");
    add_chat("We Easterlings run this area.");
    add_chat("I used to be a farmer 'til we went to war.");
    
    set_random_move(4);
    set_restrain_path(RHUN_DIR+"tower/inside");

}

