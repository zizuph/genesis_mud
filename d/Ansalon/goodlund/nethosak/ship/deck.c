inherit "/d/Krynn/std/deck";
#include "/d/Ansalon/goodlund/nethosak/ship/local.h"
#include <stdproperties.h>

void
create_deck()
{
    set_short("Deck of 'The Gladiator'");
    set_long("You stand upon the deck of large and glorious ship. "+
             "It's sleek curves are designed to sail quickly through "+
             "the waters of the Bloodsea, making it one of the "+
             "fasters ship around. Two tall masts are placed in the "+
             "center of the ship, and the two sails makes the ship "+
             "seem even more great. A thick wooden doors leads further "+
             "down into the cabin.\n");

    add_item("door","This wooden door leads to the " +
      "cabin below.\n");

    add_item("deck","The deck has been lmade out of the thick "+
       "boards, perhaps made out of oak wood.\n");
    add_item(({"line","lines","rope","ropes"}),"The lines are " +
      "stout ropes connected to the sails above.\n");
    add_item("sails","The two great sails billow above you " +
      "as a strong wind off the Bloodsea blows past.\n");

    add_exit("cabin","down",0);

    set_deck_sound("@@sounds");
}

sounds()
{
    if (random(2))
	return "The ships hull cracks loudly as it sways with the wind.\n";

    return "The ship sails gently though the water.\n";
}

