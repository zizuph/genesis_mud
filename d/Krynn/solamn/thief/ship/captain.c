
#include "/d/Krynn/common/defs.h"

inherit M_FILE
/* inherit "/d/Genesis/ship/captain"; 
 * we do the stuff ourselves, cause the std/captain doesn't have
 * some of the nice handy things that the Krynn/std/monster has.
 */

#include "local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <money.h>
#include <cmdparse.h>
#include <composite.h>

string gDestination = 0;
object gShip = 0;

void
create_krynn_monster()
{
    set_name("threefinger");
    add_name("captain");
    set_living_name("threefinger");
    set_race_name("human");
    add_adj("sturdy");
    set_adj("sinister");
    set_extra_long("He looks like he doesn't have a fixed schedule or " +
		   "destination. Maybe you could talk with him about it.\n");
    set_stats(({ 80, 120, 100, 60, 60, 90 }));
    set_skill(SS_SWIM, 100);
    set_skill(SS_LOC_SENSE,100);
    set_skill(SS_UNARM_COMBAT,30);
    set_skill(SS_DEFENCE,50);
    set_skill(SS_AWARENESS,60);
    set_skill(SS_WEP_KNIFE,80);
    set_skill(SS_BACKSTAB, 60);
    set_skill(SS_PICK_POCKET, 60);
    heal_hp(10000);
    set_chat_time(9);

    add_chat("I was really lucky to get these minotaurs, they're doing a good job.");
    add_chat("The sea is really low today, good for passenger travel, but " +
	     "not exactly my kind of thing.");
    add_chat("Palanthas is the worst city I know. But what can you do, " +
	     "there's loads of money there.");
    add_chat("The proprietor of the Inn in Palanthas is a real goof. He's " +
	     "always having problems.");
    add_chat("I guess it's time to go raid Palanthas again soon.");

    set_cchat_time(11);
    add_cchat("Stop it, you pestering dog!");
    add_cchat("Right, you'll pay for that!");
    add_cchat("Come on! I'll beat the living daylights out of you!");
    add_cchat("Right! I'm really gonna stump you this time!");
    add_cchat("Give it to me, big-nose!");
    add_cchat("I'm gonna smack you so hard....");

    set_introduce(1);
    set_title("Gloome, Captain of the Skull'n'Bones");

    add_ask("[about] 'destinations' / 'trip' / 'deal' / 'schedule'",
	    "say Well, we have " + sizeof(PLACES) + " different destinations " +
	    "to offer:\n" + COMPOSITE_WORDS(PLACES) + ". To go to either of " +
	    "the destinations, you have to buy a ticket. Then you can ask " +
	    "me to take you to one of these locations, of course. Please " +
	    "ask me about the destinations regularly, as I will most likely " +
	    "sail to additional places soon.",1);
    add_ask("[about] 'destination'","tell_destination",2);
    add_ask("[about] 'ship'","say It's a beauty, ain't it? Wanna go for a trip?\n",1);
    add_ask("[lets] [let's] [to] [sail] [take] [me] [go] [to] %s",
	    "set_destination",2);

    add_prop(OBJ_M_NO_ATTACK,
	     "You feel this man is under strong protection.\n");
}    

void
init_living()
{
    ::init_living();
    ADA("buy");
}

int
buy(string str)
{
    object buy_ob, *tmp;
    string what, from;
    int    *result, m_res, price;
    
    NF("Buy what?\n");
    if (!str)
      return 0;

    if (sscanf(str, "%s from %s", what, from) != 2)
    {
	what = str;
	from = "";
    }

    NF("I have no such thing for sale.\n");
    if (what != "ticket")
      return 0;

    NF("Buy ticket from whom?\n");
    if (strlen(from) &&
	(!sizeof(tmp = FIND_STR_IN_OBJECT(from, environment(this_player()))) ||
	 this_object() != tmp[0]))
      return 0;

    /* This guy doesn't care about these things...
    if (this_player()->query_prop("_live_i_killed_captain")) {
	notify_fail("I refuse to sell tickets to people killing my brethren!\n");
	return 0;
    }*/

    buy_ob = clone_object(TICKET);
    NF("I seem to be out of tickets.\n");
    if (!buy_ob)
      return 0;

    if (!MONEY_ADD(this_player(), -PRICE))
    {
	buy_ob->remove_object();
	write("You cannot afford the ticket.\n");
	return 1;
    }

    if (buy_ob->move(this_player()))
    {
	write("You drop the " + buy_ob->short() + " on the ground.\n");
	say(QCTNAME(this_player()) + " drops one " + buy_ob->short() +
	    " on the ground.\n");
	buy_ob->move(environment(this_player()));
    }
    else
    {
	write("You get your " + buy_ob->short() + ".\n");
	say(QCTNAME(this_player()) + " buys a " + buy_ob->short() + ".\n");
    }
    return 1;
}

string
tell_destination(object asker)
{
    if (gDestination)
      command("say Well, next time I take to the sea I am most likely bound for " +
	      gDestination + ".");
    else
      command("say Well, dunno yet. If ya wanna go someplace, maybe we can make " +
	      "a deal. Just ask me about it.");
    return "";
}

string
set_destination(object asker, string where)
{
    string txt;

    if (member_array(C(L(where)),PLACES) < 0)
    {
	if (asker)
	  command("say I'm afraid I don't go to this destination.");
	return "";
    }
    
    if (!gShip ||
	gShip->query_present_location() != find_object(SECRETPIER) ||
	gShip->query_board_enabled())
    {
	if (asker)
	  command("say I don't accept new destinations right now.");
	return "";
    }

    call_other(gShip,"set_" + L(where) + "_tour");
    if (asker)
      command("say Deal! Our next destination will be " + C(L(where)) + ".");
    gDestination = C(L(where));
    if (asker)
    {
	/*gShip->set_board_enabled(1);*/
	move_living("boarding the ship to prepare for the journey",
		    gShip->query_deck()[0]);
	gShip->start_ship(0);
	seteuid(getuid());
	txt = sprintf("%s %s asked: %s\n",
		      ctime(time())[4..15],
		      asker->query_name(),
		      gDestination);
	log_file("secretship",txt,20000);
	find_player("aridor")->catch_msg(txt);
    }
    return "";
}

void
reset_destination()
{
    gDestination = 0;
}

void
set_ship(object ship)
{
    gShip = ship;
}
