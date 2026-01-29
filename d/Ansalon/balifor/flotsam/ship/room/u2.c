#include "/d/Ansalon/balifor/flotsam/ship/local.h"
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include <macros.h>

inherit "/d/Krynn/std/deck";

object minotaur;

void
reset_deck()
{
    seteuid(getuid(TO));
    if(!objectp(minotaur))
    {
	minotaur = clone_object(FNPC + "minotaur");
	minotaur->arm_me();
	minotaur->move(TO);
    }
}

void
create_deck()
{

    set_short("The upper aft deck by the helm");
    set_long("You stand high on the upper aft deck, looking " +
      "down over the main deck and the sea around you. Here " +
      "is where the great helm stands, the large spoked wheel " +
      "that steers the ship. A wooden stairway leads down to the " +
      "main deck from here.\n");
    add_item(({"upper aft deck","aft deck"}),"You stand " +
      "on the upper aft deck of the ship. Apart from the " +
      "helm, there is nothing of interest up here.\n");
    add_item("main deck","From up here you can see all of the " +
      "main deck, where sailors scurry from port to starboard, " +
      "or aft to port, at the orders of its infamous captain.\n");
    add_item(({"sea","Blood Sea"}),"The great expanse of the " +
      "Blood Sea lies before you, and even though beneath its " +
      "turbulent waves you have no doubt many a sailor has found " +
      "his grave, its beauty is both calming and refreshing.\n");
    add_item(({"stairs","stairway","wooden stairway"}),
      "A wooden stairway leads down to the main deck from here.\n");
    add_item(({"helm","great helm","large spoked wheel",
	"spoked wheel","wheel"}),
      "In the center of the deck stands the great helm, a " +
      "large spoked wheel that steers the ship.\n");

    add_cmd_item(({"helm","great helm","wheel"}),
      ({"turn","spin","steer","pull","push"}),"@@turn_helm");

    add_exit("d9","down",0);
    reset_deck();
}

string
turn_helm()
{
    write("Although very tempted to play with the great helm, " +
      "you decide it would be wiser to leave the steering " +
      "of the ship to the professionals.\n");
    say(QCTNAME(TP) + " looks wistfully at the great helm.\n");
    return "";
}

sounds()
{
    if (random(2))
	return "The ship sways with the wind.\n";

    return "The ship rocks violently to the tune of the turbulent waters.\n";
}

