#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

inherit FLOTSAM_IN;

object door;
object ogre, human, smuggler;

void
reset_flotsam_room()
{
    if(!objectp(ogre))
    {
	ogre = clone_object(FNPC + "half_ogre");
	ogre->arm_me();
	ogre->move(TO);
    }

    if(!objectp(human))
    {
	human = clone_object(FNPC + "crafty_human");
	human->arm_me();
	human->move(TO);
    }

    if(!objectp(smuggler))
    {
	smuggler = clone_object(FNPC + "smuggler");
	smuggler->arm_me();
	smuggler->move(TO);
    }
}

create_flotsam_room()
{
    set_short("A run-down room in the Jetties Inn");
    set_long("@@long_descr");

    add_item(({"circular wooden table","wooden table","table"}),
      "This circular wooden table is used by smugglers to make " +
      "shady deals. A dim oil lamp sits in the middle of it.\n");
    add_item("lamp","A battered oil lamp sits in the middle " +
      "of the table.\n");
    add_item("stools","Two wooden stools sit around the table.\n");
    add_item("bed","From the looks of the dust covered bed, " +
      "you gather this room is not used to sleep in. \n");
    add_item("door","A closed door stands at the back of the room.\n");

    door = clone_object(FOBJ + "window1b");
    door->move(TO);

    add_cmd_item("door","open","@@open_door");

    reset_flotsam_room();
}

string
long_descr()
{
    return "You stand in a run-down room in the Jetties Inn. " +
    "A circular wooden table sits in the middle of the room " +
    "and is surrounded by two stools. An unused bed sits in " +
    "corner. On the southern wall a window looks out onto an " +
    "alley. On the opposite wall stands a closed door. \n";
}

string
open_door()
{
    write("You try and open the door but it seems to be jammed!!!\n");
    say(QCTNAME(TP) + " tries and opens the door but it appears to " +
      "be jammed. \n");

    return "";
}
