#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"

inherit AM_FILE
inherit "/lib/unique";

#define WEP BOBJ + "clabbard"
#define WEP2 "/d/Ansalon/goodlund/nethosak/city/obj/weapon/side_dagger"
#define WEP3 "/d/Ansalon/kalaman/obj/weapon/w_tessto"

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("pirate");
    add_name("minotaur");
    set_short("minotaur pirate");
    set_race_name("minotaur");
    set_long("This large minotaur is the firstmate for " +
      "the ship Drenaol's Folly. His eyes glitter angrily, " +
      "and you get the feeling this one wouldn't need much of " +
      "an excuse to rip someone into tiny pieces!\n");

    set_stats(({150 + random(25),
	75 + random(30),
	140 + random(20),
	90,
	90,
	90 + random(15)}));
    set_hp(10000);

    set_alignment(0);
    set_knight_prestige(50);
    set_all_hitloc_unarmed(25);

    set_skill(SS_WEP_SWORD, 70);
    set_skill(SS_WEP_CLUB, 70);
    set_skill(SS_DEFENCE, 60);
    set_skill(SS_PARRY, 75);
    set_skill(SS_AWARENESS, 60);
    set_skill(SS_WEP_KNIFE, 60);
    set_skill(SS_2H_COMBAT, 60);

    set_act_time(4);
    add_act("shout Hard to port!");
    add_act("shout Get up that mast you scurvy dog! Quit " +
      "slackin', or the captain will whip yur hide!");
    add_act("emote turns the helm at the command of his " +
      "captain.");
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
    clone_unique(WEP, 5, WEP3)->move(this_object(),1);

    command("change grip");
    command("wield all");

}
