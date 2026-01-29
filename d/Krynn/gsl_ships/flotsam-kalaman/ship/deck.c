inherit "/d/Krynn/std/deck";
#include "/d/Ansalon/balifor/flotsam/ship2/local.h"
#include <stdproperties.h>

void
create_deck()
{
    set_short("Deck of the Perechon");
    set_long("You stand upon the deck of " +
	"a fit and trim ship. Designed for swift sailing " +
	"and quick maneuvers, this ship is ideal for outrunning " +
	"the large dragonarmy warships, as well as ideal " +
	"for raiding the slow merchant ships that sail " +
	"the Bloodsea. Above you great sails billow with " +
	"the wind, and lines creak ominously. A wooden door " +
	"leads down into the captain's cabin.\n");

    add_item("door","This wooden door leads to the " +
      "cabin below.\n");
    add_item("deck","The deck has been lovingly " +
      "polished, and kept in perfect condition.\n");
    add_item(({"line","lines","rope","ropes"}),"The lines are " +
      "stout ropes connected to the sails above.\n");
    add_item("sails","Great white sails billow above you " +
      "as a strong wind off the Bloodsea blows past.\n");
    add_item(({"the Perechon","perechon","the perechon","Perechon"}),
      "You stand upon the deck of the Perechon. Designed for swift sailing and " +
      "quick maneuvers, this ship is ideal for outrunning " +
      "the large dragonarmy warships, as well as ideal for " +
      "raiding the slow merchant ships that sail the Bloodsea.\n");

    add_exit("cabin","down",0);

    set_deck_sound("@@sounds");
}


sounds()
{
    if (random(2))
	return "The ship sways with the wind.\n";

    return "The ship rocks violently to the tune of the turbulent waters.\n";
}

