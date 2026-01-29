
/*
 * merchant.c
 * Vegetable merchant
 * Town of Haven
 * Tibbit, 16 Feb 1998
 *
 */

inherit "/d/Krynn/std/monster";

#include "../local.h"
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>


void
create_krynn_monster()
{

    set_race_name("human");
    set_name("merchant");
    add_name("_haven_vegetable_merchant_");
    set_adj("vegetable");
    add_adj("cheerful");

    set_gender(0);

    set_short("cheerful vegetable merchant");
    set_long("While the simple people of Haven will not "+
        "spend money on jewels and other valuables, "+
        "they recognize a good deal. This gentleman is selling "+
        "vegetables of good quality, which are of great interest "+
        "to the citizens indeed.\n");

    set_stats(({
        20 + random(15),
        18 + random(15),
        20 + random(15),
        14 + random(15),
        17 + random(15),
        15 + random(15) }));

    set_skill(SS_WEP_KNIFE, 20);
    set_skill(SS_PARRY, 10);
    set_skill(SS_DEFENSE, 12);
    set_skill(SS_UNARM_COMBAT, 10);

    set_act_time(14);
    add_act("smile");
    add_act("say Would you care to sample some of my fine vegatables?");
    add_act("emote displays a fine turnip for all to see.");
    add_act("say Only a few parsnips left; get them "+
        "while they're fresh!");

    add_ask("[about] 'vegetable'/'vegetables'",
        "say I have quality celery, carrots, turnips, parsnips "+
        "and potatoes for sale.  All are locally grown.",1);
    add_ask("[about] 'celery'/'celeries'/'celerys'",
        "say I celery by the simple stalk.  It is the "+
        "least hardy of the local vegetables, but the "+
        "most tasty, some folks say.",1);
    add_ask("[about] 'carrot'/'carrots'",
        "say Note the bright color and good texture of these "+
        "carrots.  Only the finest!",1);
    add_ask("[about] 'parsnip'/'parsnips'",
        "I only have a few of these parsnips left. Get them "+
        "while you can!",1);
    add_ask("[about] 'turnip'/'turnips'",
        "say Turnips are one of the hardiest vegetables; "+
        "they'll grow about anywhere. I recommend serving "+
        "them boiled in a light ale, with cheese on top.",1);
    add_ask("[about] potato / potatoes",
        "say Potatoes are new to some people, although they've "+
        "been around Krynn since before the Cataclysm. "+
        "It's like a sweeter turnip; try some!", 1);

    add_prop(LIVE_I_NEVERKNOWN,1);

    set_alarm(0.5,0.0,"arm_me");

}

void
arm_me()
{
    reset_euid();

    clone_object(HWEP+"knife")->move(TO);

    command("wield all");

}

