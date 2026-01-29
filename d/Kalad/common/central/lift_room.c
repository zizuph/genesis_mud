#pragma strict_types
#pragma no_clone

inherit "/d/Kalad/room_std";

#include "default.h"
#include "../port/lift.h"

object winchman;

void
reset_room()
{
    if (!objectp(winchman))
    {
	winchman = clone_object(PORT + "winchman");
	winchman->move_living("M", TO);
	tell_room(TO, QCTNAME(winchman) + " arrives.\n");
    }
}

void
create_room()
{
    ::create_room();

    hear_bell = 3; /*loud: central district outdoors */

    set_short("five-way Intersection");
    set_long(
      "You are standing in a five-way intersection. " +
      "Market Street, High Street, and Caravan Street " +
      "lead off to the northwest, north, and northeast " +
      "respectively. To the south, a short wall " +
      "runs along massive cliffs and Precipice " +
      "Run follows it to the east and west. It is just " +
      "high enough to prevent accidents without blocking " +
      "the stunning view of the Bay of Kabal. " +
      "Huge wooden cranes lower straw baskets and iron " +
      "platforms to transport goods and passengers down the " +
      "side of the cliff to the city's port below. " +
      "With just one of these winches in operation, you see "+
      "several more hanging useless nearby with a sign "+
      "standing in between them.\n"+
      "@@basket@@");

    clone_object("/d/Genesis/obj/donation/column")->move(this_object(),1);
    add_item("sign","@@sign");
    add_cmd_item("sign","read","@@sign");
    add_item(({"short wall","wall"}),"A stone wall that prevents people "+
      "and trade goods from falling off the cliff.\n");
    add_item(({"bay of kabal","bay"}),"A magnificent blue bay, whose "+
      "expansive waters sparkle in the Kaladian sun.\n");
    add_item(({"huge wooden cranes","huge cranes","wooden cranes",
	"cranes","crane"}),
      "Large contraptions used in lowering people and goods to the Port "+
      "District below.\n");
    add_item(({"winches","winch"}),"The machines used to lower items "+
      "to the port at the bottom of the cliff.\n");

    add_exit(CENTRAL + "market/s0", "northwest");
    add_exit(CENTRAL + "high/s5", "north");
    add_exit(CENTRAL + "caravan/s9", "northeast");
    add_exit(TRADE + "cliffside/cliffside8", "east");

    reset_room();
}

string
basket()
{
    switch (LIFT->query_lift_status())
    {
    case MOVING_DOWN:
        return "The lift seems to move a basket downwards.\n";
        break;
    case MOVING_UP:
        return "The lift seems to be raising a basket towards you.\n";
        break;
    }

    switch (LIFT->query_lift_location())
    {
    case AT_BOTTOM:
	return "The lift is quiet, no basket is here, however.\n";
        break;
    case AT_TOP:
        return "A basket hangs over the cliff before you.\n";
        break;
    }
}

public int
all_aboard(string str)
{
    int tmp;

    if (str != "basket" && str != "wooden basket")
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    tmp = LIFT->query_lift_status();
    if (((tmp > LIFT_READY) && (tmp < LIFT_RESTING)) ||
        (LIFT->query_lift_location() != AT_TOP))
    {
        write("The basket is not here to "+ query_verb() +".\n");
        return 1;
    }

    write("You climb aboard the basket.\n");
    tell_room(TO, QCTNAME(TP) + " boards the basket.\n", TP);
    tell_room(LIFT, QCTNAME(TP) + " enters the basket.\n", TP);
    set_dircmd("basket");
    TP->move_living("M", LIFT);
    return 1;
}

void
init()
{
    ::init();

    add_action(all_aboard, "board");
    add_action(all_aboard, "enter");
}

string
sign()
{
    return "Access to the Market District is presently unavailable to "+
    "foreigners. Access may be granted barring the decision of the "+
    "City Council. You are duly encouraged to return back to the Port "+
    "District below, or to the Central District in the north, or Trade "+
    "District in the east.\n";
}
