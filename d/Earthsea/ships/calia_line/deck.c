inherit "/d/Genesis/ship/deck";

#include "/sys/macros.h"
#include "defs.h"
#include "/sys/stdproperties.h"

void
create_deck()
{
    set_short("Teak deck");
    set_long(break_string("You are standing on a deck crafted "+
	"from planks of dark, oiled teak. Coils of rope are neatly "+
	"arranged on the deck, and the rails are fashioned from "+
	"polished bronze. There are two masts on this ship, a "+
	"mainmast and a mizzen mast about half way back to the rudder. "+
	"Looking up, you see a small blue flag at the top of "+
	"the mainmast, where a crow's nest sits high above. "+
	"The white sails are embellished with the figure "+
	"of a silver hawk diving into the sea. "+
	"On the prow of the boat there is a figurehead "+
	"painted silver. You see a small hatch with a narrow "+
	"stairway leading downward.\n", 70));

    add_item("figurehead",
      "The figurehead is carved in the shape of a "+
      "hawk's face.\n");
    add_item((({"deck", "teak deck"})),
      "Clearly the ship is well maintained, as you "+
      "see from the appearance of this deck.\n");
    add_item("rails",
      "The rails are made from polished bronze "+
      "and run the length of the ship.\n");
    add_item((({"rope", "coils of rope"})),
      "The rope is neatly coiled and ready for "+
      "hawling anchor.\n");
    add_item((({"masts", "mainmast", "mizzenmast"})),
      "You can tell this is a ketch by the configuration of "+
      "the two masts, the larger mainmast and the mizzen mast, "+
      "which is a bit smaller than the mainmast and set "+
      "between the mainmast and the rudder.\n");
    add_item("mast", "Which one, the mainmast or the "+
      "mizzenmast?\n");

    add_exit(CALIA_LINE + "cabin", "down");

    set_deck_sound("@@sounds");
    set_bump_sound("The boat arrives at the pier.\n");
}

string
sounds()
{
    int i = random(7);

    switch(i)
    {
    case 0:
	return "The ship pitches down into a valley between the "+
	"huge waves.\n";
	break;

    case 1:
	return "The captain sets the sails to tack against the "+
	"wind. You duck just in time as the mainsail swings across "+
	"just above your head.\n";
	break;

    case 2:
	return "A great wave washes on the deck making a "+
	"roaring sound.\n";
	break;

    default:
	return "The deck pitches under your feet as the ship "+
	"rides the high waves.\n";
	break;
    }
}
