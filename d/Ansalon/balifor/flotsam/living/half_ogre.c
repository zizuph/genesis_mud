#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit AM_FILE
inherit "/lib/unique";

#define WEP FOBJ + "weapon/tessto"
#define ARM FOBJ + "armour/chain"

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("bodyguard");
    add_name("half-ogre");
    add_name("ogre");
    add_name("half ogre");
    set_short("half-ogre bodyguard");
    set_race_name("half-ogre");
    set_long("This huge eight foot tall half-ogre bodyguard " +
      "has to stoop to stand in this room, but that does " +
      "little to diminish his awesome size.\n");

    set_stats(({160,120,160,80,80,100}));
    set_hp(10000);

    set_aggressive(1);
    set_alignment(0);
    set_knight_prestige(50);

    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_DEFENCE, 85);
    set_skill(SS_PARRY, 75);
    set_skill(SS_AWARENESS, 60);

    set_cact_time(0);
    add_cact("emote mumbles: Smeggin' intruders! Yur meat fella!");
    add_cact("emote roars like a savage animal!");
    add_cact("laugh wicked");

}

void
arm_me()
{
    seteuid(getuid(TO));
    clone_unique(WEP, 5, "/d/Ansalon/kalaman/obj/weapon/w_tessto")->move(TO, 1);
    command("wield all");
    clone_object(ARM)->move(TO,1);
    command("wear all");

}
