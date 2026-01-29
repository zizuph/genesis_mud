#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"

inherit AM_FILE

string *gAdj1 = ({"burly","sullen","handsome","excited",
  "muscular","friendly","jovial","red-faced",
  "ugly","big-eared","big-nosed","tall","short","fat"});

#define WEP1 "/d/Ansalon/common/wep/sword/sabre"
#define WEP2 "/d/Ansalon/common/wep/sword/cutlass1"
#define WEP3 "/d/Ansalon/common/wep/sword/cutlass2"
#define FARM "/d/Ansalon/balifor/flotsam/obj/armour/"

#define PEARL "/d/Genesis/gems/obj/pearl"
#define sX 100 + random(60)

#ifndef ONE_OF
#define ONE_OF(x)  (x[random(sizeof(x))])
#endif

void
create_krynn_monster()
{
    if (!IS_CLONE)
	return;

    set_name("sailor");
    set_adj(ONE_OF(gAdj1)); 
    set_short(query_adj() + " sailor");
    set_race_name("human");
    set_long("You look upon the muscular figure of one of " +
      "the many sailors who ply a living on the Bloodsea of Istar.\n");
    set_stats(({sX,sX,sX,sX,sX,90}));
    set_hp(10000);

    set_skill(SS_WEP_CLUB, 50 + random(50));
    set_skill(SS_WEP_SWORD, 50 + random(50));
    set_skill(SS_WEP_AXE, 50 + random(50));
    set_skill(SS_DEFENCE, 30 + random(70));
    set_skill(SS_PARRY, 30 + random(70));

    set_alignment(0);
    set_all_hitloc_unarmed(20); 


    set_act_time(random(7) + 5);
    add_act("ahoy Ahoy landlubber!");
    add_act("assist");
    add_act("peer");
    add_act("shout All hands to deck!");
    add_act("say I can't wait until I get to Flotsam! I could do with " +
            "a strong drink!");
    add_act("emote trims the sails slightly.");

    set_cact_time(0);
    add_cact("assist");
    add_cact("shout To arms! Pirates!");
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
    clone_object(FARM + "bandana1")->move(TO,1);
    command("wear all");
    if(random(5) == 1)
	clone_object(PEARL)->move(this_object(), 1);
}
