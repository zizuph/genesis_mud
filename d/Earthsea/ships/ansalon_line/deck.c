inherit "/d/Genesis/ship/deck";

#include "/sys/macros.h"
#include "defs.h"
#include "/sys/stdproperties.h"

void
create_deck()
{
    set_short("Pine deck");
    set_long(break_string("The deck is constructed of pine "+
	"planks stained dark by wind, weather and sea water. "+
	"Although seaworthy, the ship appears a bit less well-"+
	"maintained than one would hope, and the aging of it causes "+
	"it to complain with creaks and moans as the wind fills "+
	"the sails of its double masts. The sails themselves appear "+
	"grey rather than white, and you can see places where they "+
	"have been patched.\n", 70));

    add_item("sails",
      "The twin set of sails appears grey from age and much "+
      "use. In some spots they appear to have been crudely "+
      "patched.\n");
    add_item((({"planks", "pine planks"})),
      "The pine planks that comprise the deck are aged and stained "+
      "from sea water and the elements.\n");
    add_item((({"masts", "mainmast", "mizzenmast"})),
      "You can tell this is a yawl by the configuration of "+
      "the two masts, the larger mainmast and the mizzen mast, "+
      "which is a bit smaller than the mainmast and set "+
      "between the mainmast and the rudder.\n");

    add_exit(ANSALON_LINE + "cabin", "down");

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
	return "The ship strains as it turns into the wind.\n";
	break;

    case 1:
	return "The captain sets the sails to tack against the "+
	"wind. You duck just in time as the mainsail swings across "+
	"your head.\n";
	break;

    case 2:
	return "The rigging creaks and moans as the wind fills "+
	"the worn sails.\n";
	break;

    default:
	return "The sails flap in the wind as the ship rocks in the "+
	"waves.\n";
	break;
    }
}
