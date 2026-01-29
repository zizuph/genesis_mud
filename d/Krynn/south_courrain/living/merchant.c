#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "../local.h"
#include "/d/Krynn/common/defs.h"
#include "/sys/money.h" 

inherit M_FILE
inherit AUTO_TEAM

#define WEP1 "/d/Ansalon/goodlund/bloodsea/obj/spear"
#define WEP2 "/d/Ansalon/goodlund/nethosak/city/obj/weapon/shortsword"

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_pick_up_team(({"sailor"}));
    set_max_team_size_auto_join(6);

    set_name("merchant");
    set_adj("wealthy");
    set_race_name("human");
    set_gender("G_MALE");
    set_short("wealthy merchant");
    set_long("Confidently standing on the rocking deck before you is a " +
       "wealthy merchant. Unlike your standard land-bound merchant, this " +
       "man is physically menacing, built strong and harsh from a life " +
       "at sea.\n");

    set_stats(({160,180,175,120,150,146}));
    set_hp(10000);

    set_all_hitloc_unarmed(50);

    set_alignment(200);
    set_knight_prestige(0);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_DEFENCE, 80);

    set_act_time(25);
    add_act("emote stands confidently on the deck of his ship.");
    add_act("emote stares at you appraisingly.");
    add_act("say It is hard to dock in Port Balifor these days, " +
        "with all the Dragonarmy ships!");
    add_act("emote looks out towards the sea.");

    equip(({ (random(2) ? WEP1 : WEP2 ), MONEY_MAKE_GC(3 + random(6)),
        MONEY_MAKE_PC(random(2)), MONEY_MAKE_SC(random(20)) }));
}

void
init_living()
{
    init_team_pickup();
    ::init_living();
}
