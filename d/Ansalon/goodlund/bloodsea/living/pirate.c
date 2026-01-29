#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"

inherit AM_FILE

string *gAdj1 = ({"burly","sullen","fork-bearded","rough",
  "mean","grim","toothless","young",
  "ugly","scarred","nasty","black-bearded","bald","one-legged"});

#define WEP1 "/d/Ansalon/common/wep/sword/sabre"
#define WEP2 "/d/Ansalon/common/wep/sword/cutlass1"
#define WEP3 "/d/Ansalon/common/wep/sword/cutlass2"
#define FARM "/d/Ansalon/balifor/flotsam/obj/armour/"

#define PEARL "/d/Genesis/gems/obj/pearl"
#define sX random(100)

#ifndef ONE_OF
#define ONE_OF(x)  (x[random(sizeof(x))])
#endif

void
create_krynn_monster()
{
    if (!IS_CLONE)
	return;

    set_name("pirate");
    set_adj(ONE_OF(gAdj1)); 
    set_short(query_adj() + " pirate");
    set_race_name("human");
    set_long("This mean looking individual is a pirate of the Bloodsea of " +
       "Istar. He makes a living plundering and pillaging, and has a heart as " +
       "black as the storm clouds over the Maelstrom.\n");
    set_stats(({50 +sX,50 + sX,50 + sX,sX,sX,50 + sX}));
    set_hp(10000);

    set_skill(SS_WEP_CLUB, 50 + (sX / 2));
    set_skill(SS_WEP_SWORD, 50 + (sX / 2));
    set_skill(SS_WEP_AXE, 50 + (sX / 2));
    set_skill(SS_DEFENCE, 30 + (sX / 2));
    set_skill(SS_PARRY, 30 + (sX / 2));

    set_alignment(-600);
    set_all_hitloc_unarmed(20); 


    set_act_time(0);
    add_act("scowl");
    add_act("emote tightens a rope at the commands of his " +
      "captain.");
    add_act("say Merchant ship to port, captain!");
    add_act("say Damn land lubbers. We should slit your throat and " +
      "chuck you overboard!");
    add_act("emote looks at you greedily, as if considering " +
      "robbing you.");
    add_act("spit");
    add_act("emote stretches his tanned muscles.");
    add_act("twinkle danger");

}

void
arm_me()
{
    int weapon = random(3);
    seteuid(getuid(TO));

    if(weapon == 0)
	clone_object(WEP1)->move(TO,1);
    if(weapon == 1)
	clone_object(WEP2)->move(TO,1);
    if(weapon == 2)
	clone_object(WEP3)->move(TO,1);
    command("wield all");
    clone_object(FARM + "shirt")->move(TO,1);
    clone_object(FARM + "bandana4")->move(TO,1);
    command("wear all");
    if(random(5) == 1)
	clone_object(PEARL)->move(this_object(), 1);
}
