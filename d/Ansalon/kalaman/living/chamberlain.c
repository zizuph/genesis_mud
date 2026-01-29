#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/kalaman/local.h"
#include "/d/Ansalon/common/defs.h"
#include <wa_types.h>
#include <money.h>

inherit AM_FILE

#define sX 60 + random(10)
#define M1  MONEY_MAKE_CC(random(13))->move(TO)
#define M2  MONEY_MAKE_SC(random(7))->move(TO)


void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("chamberlain");
    set_adj("solemn");
    set_race_name("human");
    set_short("solemn chamberlain");
    set_long("This is the chamberlain of the court of Kalaman. " +
      "He controls all access to the Lord, as well as runs " +
      "the day to day affairs of the estate.\n");

    set_stats(({sX,sX,sX,sX,sX,sX}));
    set_hp(10000);

    set_alignment(200);
    set_knight_prestige(-3);
    set_skill(SS_WEP_POLEARM, 60);
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_PARRY, 50);
    set_skill(SS_AWARENESS, 30 + random(25));
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(CONT_I_WEIGHT, 70000 + random(10000));
    add_prop(CONT_I_HEIGHT, 160 + random(40));

    set_act_time(40);
    add_act("say Lord Calof is not to be disturbed.");
    add_act("emote shouts at a servant for being lazy.");
    add_act("smile know");

    set_default_answer("The chamberlain has nothing of importance "+
      "to say.\n");
    add_ask(({"pass","upstairs","passage","calof"}),
      "say I may only allow Calof's advisors passage upstairs.",1);

}

void
arm_me()
{

    seteuid(getuid(TO));

    clone_object(KOBJ + "/weapon/staff")->move(TO);
    M1;
    M2;
    command("wield all");
    command("wear all");
}

