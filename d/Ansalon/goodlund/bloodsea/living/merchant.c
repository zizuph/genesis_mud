#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/goodlund/bloodsea/local.h"
#include "/d/Ansalon/common/defs.h"
#include "/sys/money.h" 

inherit AM_FILE
inherit AUTO_TEAM

#define WEP1 BOBJ + "spear"
#define WEP2 "/d/Ansalon/goodlund/nethosak/city/obj/weapon/shortsword"
#define WEP3 "/d/Ansalon/common/wep/sword/rapier"


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
    add_act("say When will this storm end? I have cargo that must make Saifhum " +
       "soon!");
    add_act("emote looks out towards the sea.");


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

    clone_object(BOBJ + "key")->move(TO,1);
    clone_object(BOBJ + "map_piece1")->move(TO, 1);

    MONEY_MAKE_PC(random(2))->move(TO);
    MONEY_MAKE_GC(3 + random(6))->move(TO);
    MONEY_MAKE_SC(random(20))->move(TO);

}

void
close_chest()
{
    command("close chest");
    command("lock chest with key");
}

void
init_living()
{
    init_team_pickup();
    ::init_living();
}
