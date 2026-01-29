inherit "/std/monster";

#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"

int is_armed = 0;

void arm_me()
{
  object obj;

  if(is_armed) return;
  is_armed = 1;
  reset_euid();

  obj=clone_object(WEAPON_DIR+"club_med");
  obj->move(TO);
  command("wield all");

  obj=clone_object(ARMOUR_DIR+"shield_med");
  obj->move(TO);
  obj=clone_object(ARMOUR_DIR+"helm_med");
  obj->move(TO);
  obj=clone_object(RHUN_DIR+"npc/chainmail");
  obj->move(TO);
  command("wear all");

  obj=clone_object(RHUN_DIR+"npc/brooch");
  obj->move(TO);
  obj->add_prop("_easterling_id_", 1);
}

void create_monster()
{
    set_alarm(itof(random(10)), 0.0, "arm_me");

    set_race_name("human");
    set_name(({"Easterling","easterling","captain"}));
    set_adj(({"Easterling","easterling"}));
    set_short("easterling captain");

    set_gender(0);
    set_alignment(-420);
    set_long("This is the captain of the Easterling troops.  He seems "+
	"well-trained, and well-disciplined.\n");
	
    add_prop(CONT_I_WEIGHT, 75*1000);
    add_prop(CONT_I_VOLUME, 75*1000);
    add_prop(CONT_I_HEIGHT, 180);
    set_stats(({70, 60, 80, 60, 60, 84}));

    set_skill(SS_UNARM_COMBAT, 30);
    set_skill(SS_DEFENCE, 62);
    set_skill(SS_WEP_CLUB,60);
    set_skill(SS_PARRY, 50);

    set_chat_time(5);
    add_chat("What are you doing here?");
    add_chat("We're on a mission.");
    add_chat("My troops are well-ordered and well-disciplined.");
}

