#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include "/d/Ansalon/common/defs.h"


inherit AM_FILE
inherit "/d/Ansalon/common/cheater";

void
create_krynn_monster()
{
    set_name("deminicca");
    set_race_name("human");
    set_adj("gaunt");
    add_adj("dirty");
    set_gender(G_FEMALE);
    set_long("This dirty gaunt woman stands here with a large "+
      "wicker cage in her hands, selling pigeons to people.\n");
    set_stats(({80,70,75,55,55,60}));
    set_skill(SS_DEFENCE, 60);
    set_skill(SS_AWARENESS, 60);
    set_skill(SS_UNARM_COMBAT, 60);
    set_all_hitloc_unarmed(10);
    set_act_time(9);
    add_act("shout Pigeons! Pigeons for sale!");
    add_act("emote curses as the pigeons inside her wicker " +
      "cage start flapping around.");
    add_act("emote peers around suspiciously.");
    add_act("say Would you like to buy a pigeon?");

    add_ask(({"pigeon","pigeons","price"}),
      "Pigeons! Only 99 copper coins each!\n");

    add_prop(LIVE_I_NEVERKNOWN, 1);
}

void
init_living()
{
    ::init_living();
    ADA("buy");
}


buy(str)
{
    object pig,who;
    NF("Buy what did you say?\n");
    if(!str  || (str != "pigeon"))
	return 0;

    if (check_cheater(TP, TO))
	return 1;
    NF("The woman says: You cannot pay the price.\n");
    if(!MONEY_ADD(TP, -99))
	return 0;

    write("You pay the woman, and she opens her cage and gets " +
      "you a pigeon.\n");
    say(QCTNAME(TP)+ " gets a pigeon from the dirty gaunt woman.\n");

    who = TP;
    pig = clone_object("/d/Krynn/solamn/vin/npc/pigeon");
    pig->set_owner(who);
    pig->move(who);
    return 1;
}
