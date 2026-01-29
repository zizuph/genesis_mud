/* Ashlar, 8 Jun 97 - a barkeeper */

#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include "/sys/money.h"
#include "/d/Ansalon/common/defs.h"

inherit AM_FILE

void arm_me();

void
create_krynn_monster()
{
    set_name("barkeep");
    add_name("barkeeper");
    add_name("_hk_barkeep_");
    set_race_name("human");
    set_adj("stout");
    add_adj("bearded");
    set_long("Judging by the man's look, he is the barkeeper of this " +
        "establishment. He has a thin black beard framing a heavy face.\n");
    set_stats(({80,65,75,50,55,70}));
    set_skill(SS_DEFENCE, 60);
    set_skill(SS_PARRY, 60);
    set_skill(SS_WEP_CLUB, 60);
    set_skill(SS_AWARENESS, 50);
    set_act_time(10);
    add_act("emote eyes the customers warily.");
    add_act("say Things usually get rowdy here at night.");
    add_act("say The city guard rarely come out here.");
    set_cact_time(7);
    add_cact("shout Guards, guards!");
    add_cact("say This is not respect!");
    add_cact("say Cursed be you for this!");

}

void
arm_me()
{
    object arm, wep;
    seteuid(getuid(TO));
    arm = clone_object(NARM+"apron");
    arm->move(TO);
    wep = clone_object(NWEP+"knobkerrie");
    wep->move(TO);
    command("wear all");
    command("wield all");
}

