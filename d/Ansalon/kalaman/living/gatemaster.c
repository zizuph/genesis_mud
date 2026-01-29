#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/kalaman/local.h"
#include "/d/Ansalon/common/defs.h"

inherit AM_FILE
inherit AUTO_TEAM
inherit "/lib/unique.c";

#define CLONE_POLE clone_unique(KOBJ+ "weapon/br_spear", 5, KOBJ+ "weapon/halberd")
#define WEP1 KOBJ + "weapon/br_spear"
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

    set_name("gatemaster");
    set_adj("stern");
    set_race_name("human");
    set_gender("G_MALE");
    set_short("stern gatemaster");
    set_long("This stern looking human is the gatemaster of Kalaman. " +
      "Unlike many gatekeepers around the realms, this one looks like " +
      "an experienced warrior, and wears the trappings of an officer " +
      "of the city guard.\n");

    set_stats(({125,125,125,100,100,115}));
    set_hp(10000);

    set_alignment(600);
    set_knight_prestige(-3);
    set_skill(SS_WEP_POLEARM, 90);
    set_skill(SS_PARRY, 75);
    set_skill(SS_DEFENCE, 75);
    set_skill(SS_AWARENESS, 90);
    // Well Armoured
    set_exp_factor(130);

    set_act_time(5);
    add_act("say Please read the sign before entering Kalaman.");
    add_act("say Greetings, welcome to Kalaman!");
    add_act("say Lord Calof has declared a State of War!");
    add_act("emote stares at you appraisingly.");
    add_act("say Reports say the red dragonarmy is getting closer.");
    add_act("emote looks out towards the harbour.");


}

void
arm_me()
{

    seteuid(getuid(TO));

    CLONE_POLE->move(TO, 1);
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
