#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/kalaman/local.h"
#include "/d/Ansalon/common/defs.h"

inherit AM_FILE
inherit AUTO_TEAM

#define WEP1 KOBJ + "weapon/sword"
#define WEP2 KOBJ + "weapon/mace"
#define WEP3 KOBJ + "weapon/halberd"
#define ARM1 KOBJ + "armour/platemail"
#define ARM2 KOBJ + "armour/winged_helmet"
#define ARM3 KOBJ + "armour/gauntlets"
#define ARM4 KOBJ + "armour/leggings"

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_pick_up_team(({"guard"}));
    set_max_team_size_auto_join(6);

    set_name("guard");
    set_adj("well-armoured");
    set_race_name("human");
    set_gender("G_MALE");
    set_short("well-armoured guard");
    set_long("Before you stands a well-armoured guard, stationed to protect " +
      "the gates of Kalaman's harbour. His stern demeanour gives you the impression " +
      "he takes his job quite seriously.\n");

    set_stats(({75 + random(30),
                75 + random(30),
                75 + random(40),
                80 + random(30),
                80 + random(30),
                80 + random(20)}));
    set_hp(10000);

    set_alignment(600);
    set_knight_prestige(-3);
    set_skill(SS_WEP_SWORD, 75);
    set_skill(SS_WEP_CLUB, 75);
    set_skill(SS_WEP_POLEARM, 75);
    set_skill(SS_PARRY, 60);
    set_skill(SS_DEFENCE, 60);
    // Well Armoured
    set_exp_factor(130);

    set_act_time(25);
    add_act("emote cleans dust off his shiny armour.");
    add_act("emote stares at you appraisingly.");
    add_act("say Reports say the red dragonarmy is getting closer.");
    add_act("emote looks out towards the harbour.");


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
    clone_object(ARM1)->move(TO,1);
    clone_object(ARM2)->move(TO,1);
    clone_object(ARM3)->move(TO,1);
    clone_object(ARM4)->move(TO,1);
    command("wear all");
}

void
init_living()
{
    init_team_pickup();
    ::init_living();
}
