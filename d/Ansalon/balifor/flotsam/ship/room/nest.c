#include "/d/Ansalon/balifor/flotsam/ship/local.h"
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"

inherit "/d/Krynn/std/deck";


object lookout;

void
reset_deck()
{
    seteuid(getuid(TO));
    if(!objectp(lookout))
    {
	lookout = clone_object(FNPC + "lookout");
	lookout->arm_me();
	lookout->move(TO);
    }
}

void
create_deck()
{

    set_short("Crows' nest");
    set_long("You stand within the crows' nest high " +
      "above the ships main deck. The rocking of the ship " +
      "seems to be more obvious up here, and you do not think " + 
      "it would be a bad thing to leave such lofty places to " + 
      "the birds.\n");
    add_item(({"nest","crows nest","crows' nest"}),
      "What you are standing in.\n");
    add_item(({"main deck","deck"}),
      "Far below you you see the crew scurrying on the main " +
      "deck to the captains' orders.\n");
    add_item(({"view","surroundings"}),
      "You look out from the crows' nest and admire the view. "+
      "Its quite spectacular. Below on the deck, you see captain "+
      "Hull Nightstar yelling commands to his crew. To the fore you "+
      "notice a ballista, obviously used as early defensive "+
      "measures against Dragonarmy vessels.\n");

    add_exit("l2","down",0);

    reset_deck();
}

sounds()
{
    if (random(2))
	return "The ship sways with the wind.\n";

    return "The ship rocks violently to the tune of the turbulent waters.\n";
}

