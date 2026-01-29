#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/estwilde/local.h"

inherit AM_FILE

#define WEP1 WEP + "spear"
#define WEP2 WEP + "gobbo_axe"
#define ARM ARMOUR + "gobbo_leather"

string *gAdj1 = ({"green-skinned","warty","fanged",
  "black-skinned","bony","small","large"});
string *gAdj2 = ({"cruel","evil","brutal","depraved",
  "red-eyed","bloodied","hunched"});

#ifndef ONE_OF
#define ONE_OF(x)  (x[random(sizeof(x))])
#endif


void
arm_me()
{
    seteuid(getuid(TO));
    if(random(2) == 1)
	clone_object(WEP1)->move(TO,1);
    else
	clone_object(WEP2)->move(TO,1);
    command("wield all");
    clone_object(ARM)->move(TO,1);
    command("wear all");

}


void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("goblin");
    set_adj(ONE_OF(gAdj1));
    add_adj(ONE_OF(gAdj2));
    set_race_name("goblin");
    set_long("Short and malicious, this goblin hunts and " +
      "pillages the plains of Solamnia. While " +
      "cowardly on their own, in a group they often work " +
      "up the courage to raid even small towns.\n" +
      "This goblin has the markings of the Bloody Skull tribe.\n");

    set_stats(({30 + random(45),
	30 + random(35),
	40 + random(45),
	30,
	30,
	94}));
    set_hp(10000);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_alignment(-450);
    set_knight_prestige(50);

    set_skill(SS_WEP_CLUB, 30 + random(30));
    set_skill(SS_WEP_AXE, 30 + random(30));
    set_skill(SS_WEP_POLEARM, 30 + random(30));
    set_skill(SS_DEFENCE, 60);
    set_skill(SS_PARRY, 30);
    set_skill(SS_AWARENESS, 10);

    set_act_time(10);
    add_act("emote screeches a goblin warcry!");
    add_act("emote grins wickedly at the thought of pillaging " +
      "Solamnian villages.");
    add_act("emote howls in bloodlust!");
    add_act("assist");

    set_cact_time(0);
    add_cact("assist");
    add_cact("say Smeg you!");
    add_cact("say Nugget heads! Take dis!");

    arm_me();

}
