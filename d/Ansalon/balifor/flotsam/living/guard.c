#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/balifor/flotsam/local.h"
#include "/d/Ansalon/common/defs.h"

inherit AM_FILE
inherit AUTO_TEAM

#define ARM1 ARMOUR + "bleggings"
#define ARM2 ARMOUR + "barmour1"
#define ARM3 ARMOUR + "bheavyboots"
#define ARM4 ARMOUR + "bhelmet"
#define WEP FOBJ + "weapon/lsword"

string
query_color()
{
    return "blue";
}

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_pick_up_team(({"guard"}));
    set_max_team_size_auto_join(4);

    set_name("guard");
    set_adj("dragonarmy");
    set_race_name("human");
    set_gender("G_MALE");
    set_short("dragonarmy guard");
    set_long("This is a soldier from the blue dragonarmy that has " +
      "occupied Flotsam. Ordered to guard the port gates, this soldier " +
      "is bored and agitated, and will not hesitate in amusing himself " +
      "by roughing up any newcomers that pass his post.\n");

    set_stats(({75,75,75,35,35,65}));
    set_hp(10000);

    set_alignment(-450);
    set_knight_prestige(300);
    set_skill(SS_WEP_SWORD, 60);
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_PARRY, 30);

    set_act_time(10);
    add_act("say By the Gods I am bored.");
    add_act("say There was another attack on a patrol last night! Someone " +
      "thinks it was knights, but where would they be coming from?");
    add_act("say Curse that knight commanding the Eastern armies! His forces " +
      "are causing us no shortage of problems!");
    add_act("say Hey! What are you doing here? This is off limits!");
    add_act("assist");

    set_cact_time(1);
    add_act("assist");

}

void
arm_me()
{
    seteuid(getuid(TO));
    clone_object(WEP)->move(TO,1);
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
