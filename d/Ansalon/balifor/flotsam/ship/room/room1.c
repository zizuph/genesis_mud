#include "/d/Ansalon/balifor/flotsam/ship/local.h"
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"

inherit "/d/Krynn/std/cabin";

object satania;

void
reset_cabin()
{
    seteuid(getuid(TO));
    if(!objectp(satania))
    {
	satania = clone_object(FNPC + "satania");
	satania->arm_me();
	satania->move(TO);
    }
}

void
create_cabin()
{

    set_short("luxurious guest cabin");
    set_long("You stand in a dimly lit cabin. While on most " +
      "ships the guest cabins tend to be small and rather " +
      "ordinary, this one is quite large and richly furnished. " +
      "A canopy bed sits at the end of the cabin, with a " +
      "heavy wooden desk off to its left. An intricately woven " + 
      "carpet lines the floor.\n");
    add_item(({"cabin","dimly lit cabin","lantern","guest cabin"}),
      "The cabin is dimly lit, as the lantern on the heavy " +
      "wooden desk has been turned down, filling the room with " +
      "shadows.\n");
    add_item("shadows","With the light in the room being so " +
      "low, there are plenty of shadows throughout it.\n");
    add_item(({"bed","canopy","canopy bed"}),
      "At the end of the cabin is a comfortable looking bed with " +
      "a thin, black silk veil that makes up the beds canopy. " + 
      "It is a bed typical of a noble, or of someone of " +
      "particularly fine taste.\n");
    add_item(({"desk","wooden desk","heavy wooden desk"}),
      "This heavy wooden desk is ornately carved with " +
      "beautiful woodland creatures. A lantern stands on " +
      "its edge, its dim light casting shadows throughout the " +
      "room.\n");
    add_item(({"intricately woven carpet","woven carpet","carpet"}),
      "At your feet is a thick, intricately woven carpet. " +
      "It would probably be worth a fortune.\n");

    add_exit("l1","out",0);

    reset_cabin();
}

sounds()
{
    if (random(2))
	return "The ship sways with the wind.\n";

    return "The ship rocks violently to the tune of the turbulent waters.\n";
}

