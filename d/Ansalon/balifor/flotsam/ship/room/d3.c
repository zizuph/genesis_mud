#include "/d/Ansalon/balifor/flotsam/ship/local.h"
#include <stdproperties.h>

inherit "/d/Krynn/std/deck";

void
create_deck()
{
    set_short("On the main deck before some stairs");
    set_long("You stand upon the main deck of the Golden " +
      "Lion, a fit and trim looking ship, built to handle the " +
      "rough waters of the Blood Sea, as well as built to " +
      "outrun the war galleys of the dragonarmies. Two masts " +
      "rise from the lower deck through the large hatchway " +
      "of the main deck, their white sails billowing in the " +
      "breeze. Sailors dash along the rigging above you, checking " +
      "for any tears, and tightening ropes along both masts. " +
      "Wooden stairs lead down from here to the lower deck.\n");

    add_item(({"wooden stairs","stairs"}),
      "Wooden stairs, slightly rotting from constant exposure " +
      "to the elements, lead down to the lower deck of the ship.\n");

    add_item(({"deck","main deck","ship","golden lion",
	"Golden Lion"}),
      "You stand upon the main deck of the Golden Lion, a ship " +
      "reputed to be the fastest to sail the Blood Sea. It is " +
      "captained by the infamous Hull Nightstar.\n");
    add_item(({"Blood Sea","blood sea","Blood Sea of Istar",
	"sea","blood sea of istar"}),
      "Braving the wild waters of the Blood Sea of Istar is the " +
      "Golden Lion, captained by the reknowned pirate Hull " +
      "Nightstar.\n");
    add_item("sailors","Above you in the rigging sailors dash " +
      "about at the orders of their captain, fixing tears in " +
      "the sails and tightening ropes.\n");
    add_item("masts","Two masts rise from the lower deck, " +
      "the foremast and the mizzen-mast.\n");
    add_item(({"mizzen mast","mizzen-mast"}),
      "The mizzen mast rises from the lower deck high into the " +
      "sky. White sails billow with the wind, making the " +
      "rigging groan slightly in protest. Gracing the top " +
      "of the mizzen mast is a crows nest.\n");
    add_item("foremast","The foremast rises from the lower " +
      "deck high into the sky. White sails billow with the " +
      "wind, making the rigging groan in protest.\n");
    add_item(({"white sails","sails"}),
      "Great white sails billow from the masts with the wind.\n");
    add_item(({"rigging","ropes","spar"}),
      "Ropes, ropes, and more ropes rise from everywhere " +
      "up the mast and along the spar.\n");
    add_item(({"crows nest","crow's nest"}),
      "The crow's nest is where the lookout scans the sea for " +
      "land, danger, or victim, depending on the circumstances.\n");
    add_item(({"large hatchway","hatchway","lower deck"}),
      "A large hatchway resides in the center of the ship, " +
      "looking down onto the lower deck.\n");

    add_exit("d4","port",0);
    add_exit("d2","starboard",0);
    add_exit("d9","aft",0);
    add_exit("l1","down",0);
}

sounds()
{
    if (random(2))
	return "The ship sways with the wind.\n";

    return "The ship rocks violently to the tune of the turbulent waters.\n";
}

