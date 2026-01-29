#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit AM_FILE

#define WEP FOBJ + "weapon/moon_axe"
#define ARM FOBJ + "armour/chain"

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("firstmate");
    add_name("minotaur");
    set_short("minotaur firstmate");
    set_race_name("minotaur");
    set_long("This large minotaur is the firstmate for " +
      "the Golden Lion. His muscular frame put behind the " +
      "helm of the ship adds a little extra to the ships' " +
      "manoeuvrability. Mind you, the ship is run so well by " +
      "the captain and crew, that this beast may have the time " +
      "to smash a few skulls while still on duty.\n");

    set_stats(({150 + random(25),
	75 + random(30),
	140 + random(20),
	90,
	90,
	90 + random(15)}));
    set_hp(10000);

    set_alignment(0);
    set_knight_prestige(50);

    set_skill(SS_WEP_AXE, 90);
    set_skill(SS_DEFENCE, 85);
    set_skill(SS_PARRY, 75);
    set_skill(SS_AWARENESS, 60);

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
    clone_object(WEP)->move(TO,1);
    command("wield all");
    clone_object(ARM)->move(TO,1);
    command("wear all");

}
