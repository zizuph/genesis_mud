/**********************************************************************
 * -                                                                - *
 * -                                                                - *
 * - Closed Thanar to new players Damaris 4/2004                    - *
 **********************************************************************/

#include "../default.h"

inherit CVAN_ROOM;

#define IS_MEMBER(ob)  (ob->test_bit("Kalad", 4, 4))
public int
members_only()
{
    if (IS_MEMBER(this_player()) || this_player()->query_wiz_level())

    {
	/* Is a member, pass through as normal */

	return 0;
    }

    write("A magical force prevents you from entering.\nYou are not a "+
      "Thanarian!\n");
    return 1;
}

object ob1;

void reset_room();

void
create_cvan_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(OBJ_I_HAS_FIRE, 1);

    set_short("The secret chamber of the Order");
    set_long("You are in the secret chamber of the Holy Order of Thanar. "+
      "The dome-shaped room is bare of any decorations save for the "+
      "ever-present symbol of Thanar, which has been engraved upon the "+
      "ceiling. A wavering image of the altar of Thanar lies just to your "+
      "west, while a glowing majestic archway lies to the east.\n"+
      "A golden plaque hangs upon the wall.\n"+
      "A golden brazier stands in the center of the room.\n");

    add_item(({ "symbol of thanar", "thanar symbol", "symbol" }), "A massive symbol "+
      "of a sun whose color has turned black as night.\n");

    add_item(({ "ceiling" }), "It is covered by the image of the Holy Order "+
      "of Thanar.\n");

    add_item(({ "wavering image", "image" }), "It looks like a doorway that "+
      "would take you to the altar.\n");

    add_item("plaque", "@@plaque");
    add_cmd_item("plaque", "read", "@@plaque");

    add_item(({ "golden brazier", "brazier" }), "A sacrificial brazier. There "+
      "are golden flames dancing within it.\n");

    add_item(({ "glowing majestic archway", "glowing archway", "majestic archway", "archway" }),
      "A stone structure, through which another place can be seen.\n");

    add_exit(CVAN + "lot/ur11", "west");
    add_exit(GUILDS + "thanar/joinroom", "east", members_only);

    set_noshow_obvious(1);

    reset_room();
}

int
check_thanar()
{
    object *ob;
    int i;

    ob = deep_inventory(TP);
    for (i = 0; i < sizeof(ob); i++)
	if(ob[i]->id("hsotoot"))
	{
	    write("You pass with ease through the archway and feel yourself "+
	      "transported to another place.\n");
	    say(QCTNAME(TP) + " passes with ease through the archway and is "+
	      "transported to another place.\n");
	    return 0;
	}
    write("You cannot seem to pass through the archway.\n");
    say(QCTNAME(TP) + " cannot seem to pass through the archway.\n");
    return 1;
}

void
reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(NPC + "order_master");
	ob1->move_living("M", TO);
    }
}

string
plaque()
{
    return "We are not accepting any new members at this time!\n"+
    "If you are a traitor and wish to leave, simply type 'leave order'.\n";
}

int
leave(string s)
{
    NF("Leave what? The Order?\n");
    if(s!="order")
	return 0;

    NF("You're not a member!\n");
    if(!present("hsotoot",TP))
	return 0;

    present("hsotoot",TP)->remove_object();

    write("As you leave the Order, an apparition of the great god Thanar "+
      "appears before you...\n"+
      "He looks disappointedly at you and says: Begone from here!\n"+
      "He then disappears.\n");
    say(QCTNAME(TP) + " leaves the Holy Order of Thanar!\n");

    return 1;
}
/**********************************************************************
 * - Commented out -------------------------------------------------- *

int
place(string s)
{
    NF("Place what into what?\n");
    if (!s) return 0;
    if(!parse_command(s,TO, "[platinum] 'coin' 'in' / 'into' [the] 'brazier'"))
	if(TP->query_race_name("hobbit"))
	    return 0;

    NF("You don't have any platinum coins.\n");
    if("/sys/global/money"->move_coins("platinum", 1,TP,ob1))
	return 0;

    say(QCTNAME(TP) + " joins the Holy Order of Thanar.\n");
    write("You receive a symbol of a dark sun.\n");
    write("To leave the Order, return here and type 'leave order'.\n");
    write("An apparition of the great god Thanar appears before you "+
      "and tells you: Welcome!\n"+
      "He then disappears.\n");
    clone_object(OBJ + "symbol")->move(TP);

    return 1;
}
 **********************************************************************/
void
init()
{
    ::init();
//  add_action(place, "place");
    add_action(leave, "leave");
}
