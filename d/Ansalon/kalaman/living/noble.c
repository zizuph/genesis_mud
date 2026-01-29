#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/kalaman/local.h"
#include "/d/Ansalon/common/defs.h"
#include <wa_types.h>
#include <money.h>

inherit AM_FILE

#define sX 45 + random(15)
#define M1  MONEY_MAKE_CC(random(13))->move(TO)
#define M2  MONEY_MAKE_SC(random(7))->move(TO)

string *gAdj1 = ({"haughty","young","rich","snooty","hawk-nosed",
  "cunning","modest","handsome","lordly"});
string *gName = ({"noble","merchant","diplomat","aristocrat","envoy"});

#ifndef ONE_OF
#define ONE_OF(x)  (x[random(sizeof(x))])
#endif

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name(ONE_OF(gName));
    set_adj(ONE_OF(gAdj1));
    set_race_name("human");
    set_gender("G_MALE");
    set_short(query_adj() + " " +lower_case(query_name()));
    set_long("This " +short()+ " is one of the many waiting on an " +
      "audience with the Lord of Kalaman.\n");

    set_stats(({sX,sX,sX,sX,sX,sX}));
    set_hp(10000);

    set_alignment(200);
    set_knight_prestige(-3);
    set_skill(SS_WEP_KNIFE, 20 + random(20));
    set_skill(SS_WEP_SWORD, 20 + random(20));
    set_skill(SS_DEFENCE, 5 + random(20));
    set_skill(SS_AWARENESS, 10 + random(25));
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(CONT_I_WEIGHT, 70000 + random(10000));
    add_prop(CONT_I_HEIGHT, 160 + random(40));

    set_act_time(40);
    add_act("say I wonder why Lord Calof is taking so long?");
    add_act("emote sniffs arrogantly.");
    add_act("say The princess is more beautiful than the sunset on a " +
      "clear evening!");
    add_act("tap");
    add_act("smile arrogant");


}

void
arm_me()
{

    seteuid(getuid(TO));

    if(random(3) == 1)
	clone_object(KOBJ + "weapon/noble_sword")->move(TO);
    if(random(4) == 1)
	clone_object(KOBJ + "armour/cap")->move(TO);
    M1;
    M2;
    command("wield all");
    command("wear all");
}

