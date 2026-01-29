#pragma strict_types

#include "default.h"
inherit PORT_ROOM;

void
create_port_room()
{
    add_prop(ROOM_I_INSIDE,1);
    set_short("Shipping Offices");
    set_long("You are standing within the Shipping Offices, a branch "+
      "of the Trading Company. This building is where information can be "+
      "found about the ships that dock here in the Port District of Kabal. "+
      "The interior is rather plain, with the only thing of interest being "+
      "a tidy wooden desk.\n"+
      "A doorway leads east.\n");
    add_item(({"interior"}),"The inside of this building is made entirely "+
      "out of large hardwood planks, all of a uniformly greyish-brown color.\n");
    add_item(({"large hardwood planks","large planks","hardwood planks","planks","plank"}),
      "The wood seems to have been freshly cut and appears very sturdy and durable.\n");
    add_item(({"tidy wooden desk","tidy desk","wooden desk","desk"}),
      "A small desk sitting neatly in the back of the room, its top "+
      "clear of paperwork and brilliantly polished.\n");
    add_item(({"doorway"}),"It leads east into another room.\n");

    add_exit(PORT + "s56", "west");
    add_exit(PORT + "s58", "east", "@@e_block");
}

int
e_block()
{
    object ledger;

    if(TP->query_invis())
	return 0;

    if (objectp(ledger = present("ledger", TP)))
    {
	write("The shipping clerk takes the ledger from you, allows you to walk "+
	  "past him into the room, and then places the ledger among the shelves filled "+
	  "with parchment.\n");
	say(QCTNAME(TP) + " gives something to the shipping clerk and disappears "+
	  "into the back room with him.\n");
	ledger->remove_object();
	return 0;
    }

    write("The shipping clerk pokes his head out from behind the door, and then "+
      "tells you to go away until you bring him his lost ledger.\n"+
      "The shipping clerk whispers to you: I lost it somewhere inside one "+
      "of the warehouses.\n");
    say(QCTNAME(TP) + " tried to go east, but was stopped by the shipping clerk "+
      "at the doorway.\n");

    return 1;
}

