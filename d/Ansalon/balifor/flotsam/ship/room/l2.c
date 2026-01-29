inherit "/d/Krynn/std/cabin";
#include "/d/Ansalon/balifor/flotsam/ship/local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>

void
create_cabin()
{

    set_short("lower deck of the Golden Lion");
    set_long("You stand upon the lower deck of the Golden " +
      "Lion in an area set aside for storage of goods. " +
      "Above you is a large open hatchway, where cargo is " +
      "lowered through from the main deck to here. At present " +
      "the lower deck is empty. Rising through the hatchway " +
      "are the ships mizzen-mast and foremast.\n");

    add_item(({"mast","masts"}),
      "Look at which mast? The mizzen-mast or the foremast?\n");
    add_item(({"mizzen-mast","mizzen mast"}),
      "Towards the rear of the deck, the mizzen-mast rises " +
      "up through the hatchway.\n");
    add_item("foremast","Towards the front of the deck, " +
      "the foremast rises up through the hatchway.\n");

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

    add_cmd_item(({"mizzen mast","mizzen-mast"}),"climb",
      "@@climb_mizzen");
    add_cmd_item("foremast","climb","@@climb_fore");

    add_exit("l1","aft",0);
    add_exit("l3","fore",0);
    add_prop(ROOM_I_INSIDE, 1);

    set_cabin_sound("@@sounds");
}

string
climb_mizzen()
{
    write("You climb the mizzen-mast up to the crows' nest.\n");
    TP->move_living("up the mizzen-mast",S_ROOM + "nest",0,0);
    return "";
}

string
climb_fore()
{
    write("Nah, you'll only get in the way of the sailors. " +
      "You don't want to make this ship ride any slower do you?\n");
    return "";
}

sounds()
{
    if (random(2))
	return "The ship sways with the wind.\n";

    return "The ship rocks violently to the tune of the turbulent waters.\n";
}

