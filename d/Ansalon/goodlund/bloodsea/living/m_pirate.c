#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"

inherit AM_FILE
inherit "/lib/unique";

string *gAdj1 = ({"burly","blunt-horned","muscular","rough",
  "mean","black-furred","long-horned","young",
  "weathered","angry","nasty"});

#define WEP BOBJ + "clabbard"
#define WEP2 "/d/Ansalon/goodlund/nethosak/city/obj/weapon/side_dagger"
#define WEP3 "/d/Ansalon/kalaman/obj/weapon/w_tessto"

#ifndef ONE_OF
#define ONE_OF(x)  (x[random(sizeof(x))])
#endif

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("minotaur");
    set_adj(ONE_OF(gAdj1)); 
    set_short(query_adj() + " minotaur");
    set_race_name("minotaur");
    set_long("This is a minotaur from the isle of Mithas. Huge and vicious, these " +
       "creatures are fearsome warriors and renown sailors of the Bloodsea.\n");

    set_stats(({100 + random(55),
	75 + random(30),
	100 + random(60),
	90,
	90,
	90 + random(15)}));
    set_hp(10000);

    set_alignment(0);
    set_knight_prestige(0);
    set_all_hitloc_unarmed(25);

    set_skill(SS_WEP_SWORD, 70);
    set_skill(SS_WEP_CLUB, 70);
    set_skill(SS_DEFENCE, 60);
    set_skill(SS_PARRY, 75);
    set_skill(SS_AWARENESS, 60);
    set_skill(SS_WEP_KNIFE, 60);
    set_skill(SS_2H_COMBAT, 60);

    set_act_time(4);
    add_act("emote growls: To the mighty go the spoils!");
    add_act("say Strange sea creatures prowl the Bloodsea now.");
    add_act("emote sniffs the salty air.");
    add_act("emote bellows loudly.");
    add_act("emote snorts like a bull.");
    set_cact_time(0);
    add_cact("emote roars: Gonna enjoy mincin' you into " +
      "weeny bits! Take this!");
    add_cact("emote lowers his horns and charges into you, " +
      "stunning you briefly.");
    add_cact("emote roars like a savage animal!");
    add_cact("laugh wicked");

}

void
arm_me()
{
    seteuid(getuid(TO));
    clone_object(WEP2)->move(TO,1);
    if(random(3) == 1)
      clone_unique(WEP, 5, WEP3)->move(this_object(),1);
    else
      clone_object(WEP3)->move(TO,1);  

    command("change grip");
    command("wield all");

}

void
equip_me()
{

    seteuid(getuid(TO));
    if(random(3) == 1)
      clone_object(BOBJ + "spyglass")->move(TO,1);
    else
      clone_object("/d/Calia/sea/objects/fish_net")->move(TO,1);  

}
