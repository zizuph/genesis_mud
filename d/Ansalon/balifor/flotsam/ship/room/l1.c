inherit "/d/Krynn/std/cabin";
#include "/d/Ansalon/balifor/flotsam/ship/local.h"
#include <stdproperties.h>

void
create_cabin()
{

    set_short("lower deck before the guests cabin");
    set_long("You stand upon the lower deck of the Golden " +
      "Lion in an area set aside for storage of goods. " +
      "Above you is a large open hatchway, where cargo is " +
      "lowered through from the main deck to here. At present " +
      "the lower deck is empty. To the aft of the ship stands " +
      "an open hardwood door that leads into the guests cabin. " +
      "Wooden stairs lead up from here to the main deck.\n");

    add_item(({"door","open hardwood door","hardwood door",
	"guests cabin","cabin"}),
      "To the aft of the ship stands the open door to the guests " +
      "cabin. Taking a peek inside reveals a rather dimly lit " +
      "room, although luxurious in nature.\n");
    add_item(({"wooden stairs","stairs"}),
      "Wooden stairs lead up to the main deck.\n");

    add_item(({"lower deck","Golden Lion","deck"}),
      "You stand upon the lower deck of the Golden Lion. At " +
      "present it is empty of cargo.\n");
    add_item(({"cargo","goods"}),
      "There is no cargo at present on the lower decks. The " +
      "reason for this is probably because of the dragonarmy " +
      "ships patrolling the Bloodsea, making life difficult " +
      "for pirates and such. Still, if this wasn't the case, " +
      "this pirate ship would be travelling much slower, and " +
      "most likely wouldn't be carrying passengers such as " +
      "yourself!\n");
    add_item(({"main deck","hatchway","open hatchway",
	"large open hatchway"}),
      "Above you is a large open hatchway, used to pass goods " +
      "from the main deck above to the lower deck.\n");

    add_exit("room1","aft","@@enter_cabin");
    add_exit("l2","fore",0);
    add_exit("d3","up",0);
    add_prop(ROOM_I_INSIDE, 1);

    set_cabin_sound("@@sounds");
}

int
enter_cabin()
{
    write("You step into the luxurious cabin...\n");
    return 0;
}

sounds()
{
    if (random(2))
	return "The ship sways with the wind.\n";

    return "The ship rocks violently to the tune of the turbulent waters.\n";
}

