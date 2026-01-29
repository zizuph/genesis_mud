#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/kalaman/local.h"
#include "/d/Ansalon/common/defs.h"
#include <wa_types.h>
#include <money.h>

inherit AM_FILE

#define sX 30 + random(10)
#define M1  MONEY_MAKE_CC(random(13))->move(TO)

string *gAdj1 = ({"thoughtful","grey-haired","wizened","wise",
  "ambitious","grim","dark-eyed"});

#ifndef ONE_OF
#define ONE_OF(x)  (x[random(sizeof(x))])
#endif

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("advisor");
    set_adj(ONE_OF(gAdj1));
    set_race_name("human");
    set_gender("G_MALE");
    set_short(query_adj() + " advisor");
    set_long("This " +short()+ " is one of the advisors " +
      "who councils the Lord of Kalaman.\n");

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
    add_act("say I believe we should address the issue of the cities defence.");
    add_act("say Lord Calof, I strongly suggest we look at the risks we take if " +
      "we form an open alliance with the Knights of Solamnia.");
    add_act("say If it wasn't for the dragons, we would be able to " +
      "hold off the dragonarmies indefinitely.");
    add_act("say Some of the citizens, especially those of the poor district, " +
      "don't like knights in the city. They blame them for not protecting " +
      "them during darkness and famine.");
    add_act("say Strange ships have been seen in the harbour.. some say " +
      "they are from distant worlds!");
    add_act("ponder");
    add_act("think");
    add_act("say ... and the kender! How are they getting into the city?");
    add_act("say ... not to mention the fall of Valkinord. Grim tidings indeed.");
    add_act("say ... I doubt it. What we should truely concern ourselves with " +
      "is the dwarven clans, gathering in the foothills of Estwilde.");


}

void
arm_me()
{

    seteuid(getuid(TO));

	M1;
    command("wield all");
    command("wear all");
}

