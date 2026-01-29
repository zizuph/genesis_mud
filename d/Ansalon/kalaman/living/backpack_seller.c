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
    set_name("merchant");
    set_race_name("human");
    set_adj("elderly");
    add_adj("white-haired");
    set_gender(G_FEMALE);
    set_long("This old lady is selling backpacks from out of a large " +
      "wicker basket here in the market place of Kalaman.\n");
    set_stats(({80,70,75,55,55,60}));
    set_skill(SS_DEFENCE, 60);
    set_skill(SS_AWARENESS, 60);
    set_skill(SS_UNARM_COMBAT, 60);
    set_all_hitloc_unarmed(10);
    set_act_time(9);
    add_act("emote croons: Backpacks! Backpacks for sale!");
    add_act("shout Backpacks! Quality leather backpacks!");
    add_act("emote inspects a leather backpack that sits at " +
      "the top of her wicker basket.");
    add_act("sigh tire");

    add_ask(({"backpack","backpacks","price","list"}),
      "Backpacks! Only 3 gold, 6 silver each!\n");

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
    if(!str || (str != "backpack"))
	return 0;

    if (check_cheater(TP, TO))
        return 1;
    NF("The woman says: You cannot pay the price.\n");
    if(!MONEY_ADD(TP, -504))
	return 0;

    write("You pay the woman, and she gets a backpack out of her wicker " +
      "basket and gives it to you.\n");
    say(QCTNAME(TP) + " buys a backpack from the elderly white-haired female human.\n");

    who = TP;
    pig = clone_object(KOBJ + "backpack");
    if (pig->move(who) != 0)
    {
    	write("Noticing that you are too burdened to carry the backpack, the woman " +
    	  "places it on the ground before you.\n");
    	say("The woman places the backpack on the ground before " + QCTNAME(TP) + ".\n");
    	/* pig?? */
    	pig->move(environment(who));
    }
    	
    return 1;
}
