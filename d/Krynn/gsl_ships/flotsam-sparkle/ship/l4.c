#include "../local.h"
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
inherit "/d/Krynn/std/cabin";

object boy;

void
reset_cabin()
{
    seteuid(getuid(TO));
    if(!objectp(boy))
    {
	boy = clone_object(FNPC + "cabin_boy");
	boy->arm_me();
	boy->move(TO);
    }
}

void
create_cabin()
{

    set_short("foremost part of the lower deck");
    set_long("You stand upon the lower deck of the Golden " +
      "Lion in an area set aside for storage of goods. " +
      "Above you is a large open hatchway, where cargo is " +
      "lowered through from the main deck to here. At present " +
      "the lower deck is empty.\n");

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

    add_exit("l3","aft",0);
    add_prop(ROOM_I_INSIDE, 1);

    reset_cabin();
}

sounds()
{
    if (random(2))
	return "The ship sways with the wind.\n";

    return "The ship rocks violently to the tune of the turbulent waters.\n";
}

