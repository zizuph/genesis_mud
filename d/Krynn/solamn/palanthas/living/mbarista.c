/* 
 * Barista who serves coffee at the coffee shop in the
 * northwest of the palatial plaza.  Bach, anyone?
 * Mortis 08.2005
 */

#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include "/d/Krynn/common/defs.h"


inherit CITIZEN;

#define MONEY 11 + random(300)

void
create_krynn_monster()
{
    set_name("carl");
	set_living_name("carl");
    set_race_name("human");
    set_adj("smiling");
    add_adj("green-aproned");
	add_name(({"philippe", "barista", "emmanuel", "carl"}));
	set_title("Philippe, Barista of The Dawnbringer");
    set_long("Behind the counter is a green-aproned, young man around twenty "
	+ "wearing a friendly and somehow knowing smile.  He is serving customers "
	+ "and operating the coffee brewers skillfully.\n");
    set_stats(({40,50,40,55,40,40}));
    set_skill(SS_DEFENCE, 15);
    set_skill(SS_AWARENESS, 35);
    set_skill(SS_UNARM_COMBAT, 10);
	set_size_descs("of normal length", "lean");
	set_appearance(15);

    add_prop(OBJ_M_HAS_MONEY, MONEY);
	set_introduce(1);
    set_act_time(12);
    add_act("say Who's next?");
    add_act("say Can I start a drink for anyone?");
    add_act("emote slowly breaks a smile with a knowing ken beyond his "
	+ "years.");
    add_act("emote inhales deeply as he fills a fresh pot of coffee from "
	+ "one of the large brewers.");
    add_act("time");
	add_act("smell");
    
    add_ask(({"coffee", "food", "price", "list"}), "Carl Philippe replies:  "
    + "Everything we serve is good.  I think you'll be satisfied with "
	+ "anything here.\n");

	add_ask(({"aesthetic", "aesthetics"}), "Carl Philippe replies:  "
	+ "Yes, a group of them often patronize The Dawnbringer at daybreak.  "
	+ "Decent enough fellows from an order of monks devoted to the study of "
	+ "scholarly learning.  The southern quarter of the city is known as the "
	+ "Aesthetics district.  There you can find their monastery, cheap "
	+ "accomodations, and the Great Library.\n");

	add_ask("library", "Carl Philippe replies:  The Great Library of "
	+ "Palanthas is just south of here off Inner Circle street.\n");

	add_armour(OBJ + "mcof_apron");
	set_alarm(2.0,0.0,"arm_me");

}

void
arm_me()
{
    seteuid(getuid(TO));
	MONEY_MAKE_GC(random(10))->move(TO);
	MONEY_MAKE_SC(25 + random(15))->move(TO);
}