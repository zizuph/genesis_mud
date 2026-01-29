/* Carridin, 11 jun 97 */
/* A fencer for Lutes Loot */
/*
 * Louie April 2006 - Set greed to 100.
 */

#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

inherit "/lib/shop";

inherit AM_FILE

void arm_me();

void
create_krynn_monster()
{
	set_name("lute");
	add_name("neraka_lute");
	set_title("the Pawnbroker");
	set_race_name("human");
	set_adj("short");
	add_adj("thin");
	set_long("This seemingly illhumored man watches you with obvious suspicion " +
		"in his eyes as you approach him. Being as he is, in the business of trade " +
		"of a more dubious nature, would explain a certain surly attitude towards " +
		"strangers.\n");
	set_stats(({75,90,75,80,80,85}));
	set_skill(SS_DEFENCE, 65);
	set_skill(SS_AWARENESS, 70);
	set_skill(SS_UNARM_COMBAT, 60);
	set_introduce(1);
	set_act_time(9);
	add_act("say Do you want to buy something?");
	add_act("say A customer as yours I can have any day.");
	add_act("think something.");
	add_act("emote looks around suspiciously.");
	add_act("say Hurry up, would you?");
	add_act("tap");

	set_alignment(20);
	set_knight_prestige(-2);

	config_default_trade();
    set_money_greed_buy(100);
    set_money_greed_sell(100);

    set_store_room(NOUTER + "red/store_room1");
	
}

void
init_living()
{
	::init_living();
    init_shop();
}

void
arm_me()
{
	seteuid(getuid());
	clone_object(NARM + "boots1")->move(TO);
	clone_object(NARM + "breeches")->move(TO);
	clone_object(NARM + "vest")->move(TO);

	command("wear all");
}
