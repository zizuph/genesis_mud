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
    set_name("foodman");
    set_race_name("human");
    set_adj("loud");
    add_adj("jovial");
    set_long("This jovial looking human is loudly hawking his " +
      "wares, which are displayed on a large tray he carries " +
      "around. From the smell, he sells food. You could probably " +
      "find out what he sells by asking him about what food " +
      "he has.\n");
    set_stats(({80,70,75,55,55,60}));
    set_skill(SS_DEFENCE, 60);
    set_skill(SS_AWARENESS, 60);
    set_skill(SS_UNARM_COMBAT, 60);
    set_all_hitloc_unarmed(10);
    set_act_time(9);
    add_act("say Anyone hungry? Got some nice food " +
      "for sale!");
    add_act("say Hey watch it! You almost knocked " +
      "my tray over!");
    add_act("emote sniffs his tray.");
    add_act("say Come on! Someone has to be hungry??");
    add_act("say Come buy the finest meat rolls this side " +
      "of Tarsis!");

    add_ask(({"tray","food","about food",
	"about what food he has","what food he has"}),
      "I am selling the finest meat rolls north of Tarsis! Made from the biggest " +
      "rolls I could find, and filled with thick chunks of beef that are covered in " +
      "gravy! And only for 80 coppers! No one could offer you a better deal!\n");

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
    NF("Buy what did you say? A meat roll?\n");
    if(!str || (str != "meat roll"))
	return 0;

    if (check_cheater(TP, TO))
        return 1;
    if(str = "meat roll")
    {
	NF("The food vendor says: You cannot pay the price.\n");
	if(!MONEY_ADD(TP, -80))
	    return 0;

	write("You pay the man, and he passes you a huge meat roll from " +
	  "off his tray.\n");
	say(QCTNAME(TP) + " buys a meat roll from the food vendor here.\n");

	who = TP;
	pig = clone_object(KOBJ + "meat_roll");
        if (pig->move(who) != 0)
        {
    	  write("Noticing that you are too burdened to carry the food, the man " +
    	    "places it on the ground before you.\n");
    	  say("The man places the food on the ground before " + QCTNAME(TP) + ".\n");
    	  /* pig?? */
    	  pig->move(environment(who));
         }
 
	return 1;
    }
    return 1;
}
