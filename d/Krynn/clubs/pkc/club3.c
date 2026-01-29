/* created by Aridor 12/01/93 */

inherit "/lib/trade";
inherit "/std/room";

#include "clubdefs.h"
#include <macros.h>
#include <money.h>

object board;

create_room()
{
    config_default_trade();
    set_short("Club Room");
    set_long(BS("This is the representative chamber of the Prestigious " +
	"Knights' Club. A squire is standing by the door, eagerly " +
	"looking you up and down. Plush carpets soften your step, " +
	"and the ceiling is lower than in the hall providing a " +
	"feeling of comfort and closeness. Since there are no windows " +
	"in the room, several lamps shed a " +
	"flickering, easing light across the room, allowing shadows " +
	"to dance along the walls. A small plaque is fastened on the north " +
	"wall. The door to the west is guarded by " +
	"another squire, whereas through the open door to the south, " +
	"the grand entrance hall of the Clubhouse can be seen.",SL));

    INSIDE;
    LIGHT;

    add_cmd_item(({"words","plaque"}),"read",
	"                The Prestigious Knights' Club\n" +
	"                -----------------------------\n" +
	"    Here in this room you can become a supporter of the Club.\n" +
	"    Only here is where you can <break faith with the Prestigious\n" +
    "    Knights' Club> if you really deem it necessary. Of course,\n" +
    "    if you leave on your free will, you may never be able to \n" +
    "    become a member again. But beware, you may find yourself not\n" +
    "    a club member even if you don't leave on your own will. The\n" +
    "    club needs active supporters, so activity is your main task\n" +
    "    n the club. In case you lose your scabbard, simply <rejoin>\n" +
    "    the club here. You can also trade your scabbard in for a\n" +
    "    holster, or vice versa, if you <switch scabbard> here.\n" +
	"    Please use the board in this room for club discussions.\n" +
	"                                   Signed,\n" +
	"                                   Lord Aridor of Palanthas.\n");
    add_item(({"plaque"}),
	BS("You can read the words on the plaque.",SL));
    add_item(({"squire","squires"}),
	BS("The squires are Squires of Solamnia, and their task is simply " +
	    "to stand there and look at everyone passing by. They are both " +
	    "not allowed to talk to you, and hope they will eventually get " +
	    "promoted to real Knights.",SL));
    add_item(({"carpets","carpet","plush"}),
	BS("These are woven carpets with intricate patterns set into them. " +
	    "Every carpet has a different color, and different types of " +
	    "material are used.",SL));
    add_item(({"symbol","symbols","pattern","patterns","color","colors","colour","colours"}),
	BS("The patterns on the carpets show the symbols of the Knights of " +
	    "Solamnia: The Crown, the Sword, the Rose and the Kingfisher, " +
	    "representing the 3 Orders and Knighthood itself. Each symbol is " +
	    "woven in different colors, contrasting the carpet itself.", SL));
    add_item(({"rose"}),
	BS("It's a woven rose with green leaves and a red blossom, on a black carpet.",SL));
    add_item(({"sword"}),
	BS("It's a sword in silver and bronze, woven into the green and red carpet.",SL));
    add_item(({"crown"}),
	BS("It's a golden crown on a white carpet.",SL));
    add_item(({"kingfisher"}),
	BS("It's a bird with a long straight bill standing in water with its long legs " +
	    "intent on some prey in the water. The kingfisher is woven in grey colors " +
	    "in blue water with a light blue sky in the background.",SL));
    add_item("ceiling",
	BS("It's a wooden ceiling furnished with light brown panels.",SL));
    add_item(({"lamps","lamp","oil lamp","oil lamps"}),
	BS("These are ordinary oil lamps, and one of the few tasks of the squires is " +
	    "to keep them lit at all times.",SL));
    add_item(({"shadow","shadows","wall","walls"}),
	BS("These shadows are very soft, cast on the walls by the oil lamps in " +
	    "the room. They seem to dance merrily along the walls.",SL));
    add_item(({"door","doors","south door","west door"}),
	BS("The door south leads into the grand entrance hall of the Club House. " +
	    "To the west you can reach the private chambers of the club. At each of " +
	    "the doors a squire stands at attention.",SL));

    add_exit(CLUB + "club1","south");
    add_exit(CLUB + "club4","west","@@club_members_only",0);

    reset_room();
}

void
init()
{
    ::init();
    ADA("support");
    ADD("break_faith","break");
    ADA("wake");
    ADA("rejoin");
    ADD("switch_scab","switch");
}


int
club_members_only()
{
    int pr = ((IS_CLUB_MEMBER(TP)) ? (1) : (0));

    if (TP->query_wiz_level())
	return 0;

    if( !pr )
    {
	write("Only clubmembers are allowed in there.\n");
	return 1;
    }
    else
    {
	write("Welcome within the private chambers.\n");
	return 0;
    }
}

void
reset_room()
{
    if (!board)
    {
	board = clone_object(CLUB + "board");
	board->move(TO);
    }
}


int
do_the_rejoin()
{
    object scab;

    /*
     * if the player is in the club list, but doesn't have a scabbard,
     *  give him one
     */
    if (!CLUBMASTER->is_no_longer_a_member(TP) && !IS_CLUB_MEMBER(TP))
    {
	scab = clone_object(SCABBARD);
	if (scab->move(TP,1))
	{
	    NF("You unsuccessfully tried to rejoin the club. " + 
		"Please leave a bug report.\n");
	    return 0;
	}
	write_file(CLUBLOG, TP->query_real_name() + " " + 
	    ctime(time())[4..15] + " Rejoined.\n");
	tell_object(TP,
	    "Here you have a new scabbard. Please be more careful with " + 
	    "this one.\n");
	return 1;
    }
    if (IS_CLUB_MEMBER(TP))
    {
	NF("You already have your scabbard.\n");
	return 0;
    }
    NF("You cannot rejoin, you're not a member.\n");
    return 0;
}

int
support(string str)
{
    string res;
    string fstr;
    NF("Support the prestigious knights' club?\n");
    if (!str)
	return 0;

    if (lower_case(str) != "the prestigious knights' club")
	return 0;

    res = (CLUBMASTER)->is_not_able_to_join(TP);
    if (!res)
    {
	tell_room(E(TP), QCTNAME(TP) + " has just joined the Prestigious " +
	    "Knights' Club!\n A scabbard is given to " + (TP->query_gender() ? "her" : "him") +
	    " from one of the squires.\n", TP);
	tell_object(TP,"Welcome in the Prestigious Knights' Club!\n" +
	    "You receive your personal scabbard from one of the squires.\n");
	return 1;
    }
    else
	if (res == "You are already a member!")
	    return do_the_rejoin();
	else
	    write(BS(res,SL));
    return 1;
}

int
break_faith(string str)
{
    string reply;
    if (!str)
	return 0;

    NF("If you want to leave the club, type 'break faith with the " + 
	"Prestigious Knights' Club'\n");
    if (str != "faith with the Prestigious Knights' Club" && 
	str != "faith with the prestigious knights' club")
	return 0;

    reply = (CLUBMASTER)->break_faith_with_the_club(TP);
    if (reply)
	write(BS(reply,SL));
    return 1;
}

int
wake(string str)
{
    int *money, price;
    seteuid(getuid(TO));
    NF("Wake up in the club?\n");
    if (!str)
	return 0;

    if (str == "up in the club")
    {
	if (TP->query_temp_start_location())
	{
	    NF("You already decided to spend your next night " +
		"somewhere else.\n");
	    return 0;
	}
	price = SLEEP_PRICE;
	if (IS_CLUB_MEMBER(TP))
	    price = SLEEP_PRICE_MEM;

	NF("It seems you don't have enough money to pay the price.\n");
	if (sizeof(money = pay(price,TP,"platinum gold silver copper",0,0)) 
	    == 1)
	    return 0;

	TP->set_temp_start_location(SLEEP);
	tell_object(TP,
	    "Ok, the next time you log in, you will start in the club.\n");
	tell_room(TO, QCTNAME(TP) + " decided to spend the next night in " + 
	    "the comfortable sleeping room of the club.\n",TP);

	return 1;
    }
    return 0;
}

int
rejoin(string str)
{
    NF("Rejoin the club?\n");
    if (!str)
	return 0;

    if (str != "club" && str != "the club" && 
	str != "the prestigious knights' club")
	return 0;
    return do_the_rejoin();
}


int
switch_scab(string str)
{
    object scab = IS_CLUB_MEMBER(TP);
    NF("Switch what?\n");
    if (!str)
	return 0;
    if (str != "scabbard")
	return 0;
    NF("You can't do that! You're not a club member.\n");
    if (!scab)
	return 0;

    scab->switch_the_scabbard();
    if (!scab->is_a_real_scabbard())
    {
	write("You trade your ornamented scabbard in for an " + 
	    "ornamented holster.\n");
	tell_room(TO, QCTNAME(TP) + " trades " + POSSESSIVE(TP) + 
	    " scabbard in for a holster.\n", TP);
    }
    else
    {
	write("You trade your ornamented holster in for an ornamented " + 
	    "scabbard.\n");
	tell_room(TO, QCTNAME(TP) + " trades " + POSSESSIVE(TP) + 
	    " holster in for a scabbard.\n", TP);
    }
    return 1;
}

