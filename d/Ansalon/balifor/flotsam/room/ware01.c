#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"
#include <macros.h>

inherit FLOTSAM_IN;
object hob1;
object hob2;

void
reset_flotsam_room()
{
    if(!objectp(hob1))
    {
	hob1 = clone_object(FNPC + "hobgob");
	hob1->arm_me();
	hob1->move(TO);
    }
    if(!objectp(hob2))
    {
	hob2 = clone_object(FNPC + "hobgob");
	hob2->arm_me();
	hob2->move(TO);
    }
}

create_flotsam_room()
{
    set_short("A great wooden warehouse in the town of Flotsam");
    set_long("@@long_descr");

    add_item(({"boxes","crates"}),
      "You count quite a few wooden crates, marked with "+
      "the insignia of the Blue Dragonarmy. These boxes are filled with " +
      "weapons, armour and supplies, stored and ready for transportation " +
      "to the armies in the West. They are securely nailed shut. \n");
    add_item("walls","The great wooden walls rise up " +
      "into the darkness of the ceiling. \n");

    add_exit(FROOM + "street12","out","@@ware_enter",0);

    add_cmd_item(({"crates","boxes"}),
      ({"open","search"}), "@@search_crates");

    reset_flotsam_room();
}


string
long_descr()
{
    return "You stand within the great wooden walls " +
    "of one of Flotsams warehouses. This high-vaulted " +
    "stone structure faces the full fury of winter sea " +
    "storms that come in from the docks, so it leans " +
    "slightly towards the inner parts of town. " +
    "Boxes of supplies, weapons and armours fill " +
    "the room. \n";
}

int
ware_enter()
{
    write("You leave the warehouse, and step into the streets of " +
      "Flotsam. \n");
    return 0;
}

string
search_crates()
{
    if ( (objectp(hob1) && E(hob1) == TO) ||
      (objectp(hob2) && E(hob2) == TO) )
    {
	hob1->command("say Hey! Keep away from those boxes!");
	hob2->command("emote steps in front of the boxes.");
	hob2->command("growl");
	return "";
    }

    write("You are unable to pry the boxes open, so "+
      "find nothing of interest.\n");
    say(QCTNAME(TP)+ " searches around the boxes vainly "+
      "in an attempt to open them.\n");
    return "";
}
