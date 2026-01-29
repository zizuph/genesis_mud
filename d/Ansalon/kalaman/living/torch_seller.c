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
    set_adj("thin");
    add_adj("hook-nosed");
    set_long("This thin hook-nosed human is carrying a large " +
      "bundle of torches on his back, bowing him over as he " +
      "wanders around the market place selling his goods.\n");
    set_stats(({80,70,75,55,55,60}));
    set_skill(SS_DEFENCE, 60);
    set_skill(SS_AWARENESS, 60);
    set_skill(SS_UNARM_COMBAT, 60);
    set_all_hitloc_unarmed(10);
    set_act_time(9);
    add_act("shout Torches! Get yur torches 'ere!");
    add_act("say These torches last for a bit!");
    add_act("say They'll keep the dark away, my torches!");
    add_act("say Want to buy a torch?");


    add_ask(({"torch","torches","price","list"}),
      "One torch, 40 copper coins each!\n");

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
    if(!str || (str != "torch"))
	return 0;

    if (check_cheater(TP, TO))
        return 1;
    NF("The man says: You cannot afford a torch.\n");
    if(!MONEY_ADD(TP, -40))
	return 0;

    write("You pay the man, and he passes you a " +
      "torch from his bundle on his back.\n");
    say(QCTNAME(TP) + " buys a torch from the " +
      "thin hook-nosed human.\n");

    who = TP;
    pig = clone_object("/d/Krynn/solace/village/obj/torch");
    if (pig->move(who) != 0)
    {
    	  write("Noticing that you are too burdened to carry the torch, the man " +
    	    "places it on the ground before you.\n");
    	  say("The man places the torch on the ground before " + QTNAME(TP) + ".\n");
    	  /* pig?? */
    	  pig->move(environment(who));
     }
 
    return 1;
}
