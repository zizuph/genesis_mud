/* coded by Torqual */

inherit "/d/Krynn/std/deck";
#include "/d/Ansalon/balifor/flotsam/ship3/local.h"
#include <stdproperties.h>

void
create_deck()
{
    set_short("Stern of the Longhorn");
   set_long("You stand upon the bottom of one of the famous " +
	"minotaur longboats. Although that one is not living up " +
	"to its name it still has more then 15 meters from stem to "+
	"here and 2 meters across the beam. On a mast, towering in "+
	"the middle, you see rectangular sail coloured red, just like "+
        "the sea the ship is sailing at.\n");

    add_item("deck","The deck has been lovingly " +
      "polished, and kept in perfect condition.\n");
    add_item(({"line","lines","rope","ropes"}),"The lines are " +
      "stout ropes connected to the sail above.\n");
    add_item("sail","Great red sail billow above you " +
      "as a strong wind off the Bloodsea blows past.\n");
    add_item(({"the Longhorn","longhorn","the longhorn","Longhorn"}),
      "You stand upon the deck of the Longhorn. Designed for swift " +
      "sailing and quick maneuvers, this ship is ideal for marine battles " +
      "as well as ideal for quick raids on the villages up the shallow "+
      "rivers. Almost all middsection is occupied by rows of oars "+
      "with two minotaurs at each.\n");
    add_item(({"middsection", "oars"}), "Middsection of the longboat "+
      "is crowded with minotaurs who sit on their benches, tightly "+
      "gripping to long oars. Each of the oars is firmly set into  " +
      "the sideboard and secured with metal cladding, oil-soaked strips "+
      "of leather wrapped at the point where wood from oars touches "+
      "metal from cladding ensure smooth and noiseless rowing. "+
      "Right in the very end of the ship, there is one large oars "+
      "probably used as a stern.\n"); 
    add_item("minotaurs", "Each of oarsmen, just like their captain, is a " +
      "minotaur. That means this this ship can travel quite fast and " +
      "has strong defensive potential.\n");

    add_exit(DECK2,"fore",0);
    
    set_deck_sound("@@sounds");
}


sounds()
{
    if (random(2))
	return "The ship gently climbs on the wave and slides down on "+
	"other side.\n";

    return "The ship swiftly swims from wave to wave propeled by strong "+
           "pushes of oars.\n";
}

