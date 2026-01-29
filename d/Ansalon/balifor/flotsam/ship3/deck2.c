/* coded by Torqual */
inherit "/d/Krynn/std/deck";
#include "/d/Ansalon/balifor/flotsam/ship3/local.h"
#include <stdproperties.h>

/* prototypes */
int check_exit();
string sounds_deck();

/* variables */
int ban_enter = 1;

void
create_deck()
{
    set_short("Deck of the Longhorn");
    set_long("You stand upon the bottom of one of the famous "+
	"minotaur longboats. Although this one does not quite live up " +
	"to that name, it still has more than 15 meters from stem to "+
	"stern and 2 meters across the beam. On a mast, towering in "+
	"the middle, you see rectangular sail coloured red, just like "+
	"the sea the ship is sailing at.\n");

    add_item("deck","The deck has been lovingly " +
      "polished, and kept in perfect condition.\n");
    add_item(({"line","lines","rope","ropes"}),"The lines are " +
      "stout ropes connected to the sail above.\n");
    add_item(({"sail", "large sail", "rectangular sail",
	 "large rectangular sail"}),"Great red sail billows above you " +
      	 "as a strong wind off the Bloodsea blows past. " +
	"It sure helps oarsmen in their hard work.\n");
    add_item("mast", "Single beam of wood is set into the bottom of " +
	"longboat providing holding for large rectangular sail.\n");
    add_item(({"the Longhorn","longhorn","the longhorn","Longhorn"}),
      "You stand upon the deck of the Longhorn. Designed for swift  " +
      "sailing and quick maneuvers, this ship is ideal for marine battles " +
      "as well as ideal for quick raids on the villages up the shallow "+
      "rivers. On both its sides there are rows of 8 oars with two "+
      "minotaurs at each. Both sides of the longboat are decorated with "+
      "various war trophies\n");
    add_item("trophies", "Among the shields of every size and shape " +
      "you can see pieces of skin and tufts of hair, some huge claws and "+
      "fangs. Some of them are still covered with dried blood.\n");
    add_item(({"minotaurs", "oarsmen"}), "Each of oarsmen  "+ 
      "is a minotaur. Their huge muscles and incredible stamina "+
      "ensure that ship will not lack the speed when in need, " + 
      "not mentioning enough sword and axes to sink anyone who would " +
      "dare to attack this ship.\n");

    add_exit(DECK1,"fore", "@@check_exit");
    add_exit(DECK3, "aft",0);
    
/*     set_deck_sound("@@sounds_deck"); */
}


string
sounds_deck()
{
    if (random(2))
	return "The ship gently climbs on the wave and slides down on "+
	"other side.\n";

    return "The ship swiftly swims from wave to wave propelled by strong "+
           "pushes of oars.\n";
}

int
check_exit()
{
	if (ban_enter)
	{
            write("One of the the minotaurs snorts something in his language "+
			"and stands in your way. He definitively does "+
			"not want you to go there.\n");
		return 1;
	}
	return 0;
}
