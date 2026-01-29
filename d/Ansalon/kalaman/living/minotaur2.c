#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit AM_FILE

#define WEP "/d/Krynn/icewall/plains/obj/taxe"
#define ARM FOBJ + "armour/chain"

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("minotaur");
    set_adj("muscular");
    set_race_name("minotaur");
    set_long("This massive minotaur most likely comes from one of the Minotaur Isles of " +
      "Kothas or Mithas. Well scarred from numerous battles, it wears these proudly " +
      "as proof of its viciousness in battle. At the moment it seems that this minotaur is " +
      "serving as a bodyguard.\n");

    set_stats(({160, 75, 140, 90, 90, 90}));
    set_hp(10000);

    set_alignment(0);
    set_knight_prestige(50);

    set_skill(SS_WEP_AXE, 90);
    set_skill(SS_WEP_CLUB, 90);
    set_skill(SS_DEFENCE, 85);
    set_skill(SS_PARRY, 75);
    set_skill(SS_AWARENESS, 60);

    set_act_time(4);
    add_act("emote sniffs the air suspiciously.");
    add_act("emote looks at you, its eyes narrowing.");
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
