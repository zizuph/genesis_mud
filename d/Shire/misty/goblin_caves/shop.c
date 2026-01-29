/*
 * /d/Shire/misty/goblin_caves/shop
 * Shop in Goblin caves
 * Milan March 1994
 * modified from:
 *  Shop in Minas Morgul
 *  Olorin, July 1993
 *  copied from:
 *  Bendar's General Store in Edoras
 *  rewritten by Olorin                   may 1993
 *  - use /lib/shop  - copied from ranger guild shop
 *  modified by Olorin                   feb 1993
 *  after ideas by Hamurabbi
 *  after the Hobbiton drug store by
 *                               Tricky, dec 1991
 *  Updated room descriptions and store descriptions
 *  -- Finwe, July 2004
 */
 
#include "/d/Shire/sys/defs.h"
#include "../local.h"
 
inherit SHIRE_ROOM;
inherit "/d/Emerald/lib/shop_list";
 
#define STORE_ROOM CAVE_DIR + "store"

static object grumphlin;
 
void
create_shire_room()
{
    config_default_trade();  /* Set up the trading system */
    set_money_give_max(1000);
    set_money_give_out(   ({ 10000,   700,  40,    1 }));
    set_money_give_reduce(({     0,     4,   3,    9 }));
    set_money_greed_sell("@@discriminate");
    set_money_greed_buy("@@discriminate");
    set_money_greed_change("@@discriminate");
    set_store_room(STORE_ROOM);

    set_short("collapsed tunnel");
    set_long("You are at the end of a collapsed tunnel under the Misty " +
        "Mountains. The walls are damp with condensation and look like " +
        "all the other tunnels. This one is slightly different than " +
        "the others. A greedy goblin has made a shop here. He may buy " +
        "or sell things offered to him. A sign is on the wall for " +
        "you to read.\n");
/*
    set_long("You are at the end of the tunnel that burrow under the Misty "
      + "Mountains. It is very humid and the walls are damp with condensed "
      + "water.  You seriously hope that you are not lost because every "
      + "tunnel looks much the same as the last...\n"
      + "But this one is slightly different. One greedy goblin made a private "
      + "shop here. If he is here he you sell or buy all kind of things he "
      + "has or you offer to him. He has made a poster explaining which you "
      + "can read. Because he doesn't want to have stolen anything he keeps "
      + "all things in small storeroom west from here.\n"
      + "There is one obvious exit: east.\n");
*/
    add_item("sign","Maybe you are literate enough to read it.\n");
    add_item("storeroom","You only see a closed door.\n");
    add_item("door","They are very massive and able to keep anyone out of " +
        "the storeroom.\n");
    
    reset_shire_room();

    add_exit(STORE_ROOM, "west", "@@wiz_check");
    add_exit(CAVE_DIR+"t60", "east");
}
 

void init()
{
    ::init();
    init_shop();
    add_action("open_door", "open");
    add_action("unlock_door", "unlock");
}

int open_door(string arg)
{
    NF("It is too dark to see.\n");
    if(!CAN_SEE_IN_ROOM(TP)) return 0;
    NF("Open what?\n");
    if(!arg || (arg != "door")) return 0;
    say(QCTNAME(TP)+" tries desperately open the door but it "+
      "remains closed.\n");
    TP->catch_msg("You try desperately open the door but it remains closed.\n");
    if(grumphlin && present(grumphlin,TO))
    {
	grumphlin->command("knee "+TP->query_real_name());
	grumphlin->command("shout Don't mess with my storeroom!!!");
    }
    return 1;
}

int unlock_door(string arg)
{
    NF("It is too dark to see.\n");
    if(!CAN_SEE_IN_ROOM(TP)) return 0;
    NF("Unlock what?\n");
    if(!arg) return 0;
    if(explode(arg+" "," ")[0] != "door") return 0;
    say(QCTNAME(TP)+" tries unlock "+arg+" but it doesn't seem to work.\n");
    TP->catch_msg("You try to unlock "+arg+" but it doesn't seem to work.\n");
    if(grumphlin && present(grumphlin,TO))
    {
	grumphlin->command("tackle "+TP->query_real_name());
	grumphlin->command("shout I will really kill you!!!");
	grumphlin->command("kill "+TP->query_real_name());
    }
    return 1;
}


void
reset_shire_room()
{
    setuid();
    seteuid(getuid());

    if(!objectp(grumphlin))
    {
        grumphlin = clone_object("/d/Shire/misty/npc/keeper");
        grumphlin->arm_me();
        grumphlin->move(TO);
    }
}

int check_grumphlin(string arg)
{
    object enemy;
    string who;

    if (grumphlin && present(grumphlin,TO))
    {
	who = TP->query_nonmet_name();
	if(grumphlin->query_introduced(TP))
	    who = TP->query_name();
	if(enemy = grumphlin->query_attack())
	{
	    if(enemy == TP)
	    {
		grumphlin->command("say Now you want to "+arg+" something? I will kill "+
		  "you now and take all your possesions for free!");
		grumphlin->command("ponder stupid "+who);
	    }
	    else
	    {
		grumphlin->command("say Please "+who+"! You must wait until I kill "+
		  "this coward "+enemy->query_nonmet_name()+"! "+
		  "Maybe you can help me too?");
		grumphlin->command("wink "+TP->query_name());
	    }
	    return 0;
	}
	else
	    return 1;
    }
    else
    {
	TP->catch_msg("There is no shopgrumphlin here, so you can't do that!\n");
	return 0;
    }
}

int check_intro(string arg)
{
    if(grumphlin->query_introduced(TP)) return 1;
    grumphlin->command("say If you want "+arg+" something then you should at "+
      "least introduce yourself!");
    grumphlin->command("say Hey you dirty cur! I mean you "+TP->query_nonmet_name()+"!");
    return 0;
}

int check_light()
{
    if(CAN_SEE_IN_ROOM(grumphlin)) return 1;
    grumphlin->command("say I am sorry "+TP->query_name()+" but I can't work "+
      "when I can't see and all my torches are gone...");
    grumphlin->command("sigh");
    return 0;
}


int
shop_hook_list_no_match(string str)
{
    NF("");
    grumphlin->command("say We have no "+str+" in stock, "+TP->query_name()+".\n");
    return 0;
}

/*
 * Function name:   wiz_check
 * Description:     Check if a player is a wizard
 * Returns:         0 if the player is a wizard
 *                  1 otherwise
 */
wiz_check()
{
    seteuid(geteuid(TO));
    if (TP->query_wiz_level())
	return 0;

    TP->catch_msg("You try to go to storeroom but bump into a closed door.\n");
    say(TP->query_name()+" tries to go to storeroom but bumps into a closed door.\n");
    if(grumphlin && present(grumphlin,TO))
    {
	grumphlin->command("grin at "+TP->query_real_name());
	grumphlin->command("shout You will not plunder my store room!");
    }
    return 1;
}

/*
 * Function name:   discriminate
 * Description:     Don't treat all players equal by giving different prices.
 * Returns:         A percentage.   100   pay normal price.
 *                                 >100   annoy player
 *                                 <100   help player
 */
int
discriminate() {
    int bargain;

    bargain = TP->query_skill(SS_TRADING);
    if(bargain > 30) bargain = 30;
    bargain = 115 - bargain;

    if(TP->query_race_name() == "goblin")
	return ((bargain * 85) / 100);

    return ((bargain * 120) / 100);
}
