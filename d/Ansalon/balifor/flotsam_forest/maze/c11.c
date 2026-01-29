#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"
#include <stdproperties.h>
inherit FOREST_IN;
object key, chest;

void
reset_flotsam_room()
{
    if(!objectp(chest))
    {
	chest = clone_object(FOBJ + "chest3");
	chest->move(TO);
    }
    if(!present(key, chest))
    {
	key = clone_object(FOBJ + "silver_key");
	key->move(chest,1);

	chest->add_prop(CONT_I_CLOSED, 1);
	chest->add_prop(CONT_I_LOCK, 1);
    }

}

create_flotsam_room()
{
    set_short("Within a minotaur maze");
    set_long("@@long_descr");

    add_item(({"walls","stone walls","great stone walls"}),
      "These great stone walls are ten feet high and riddled " +
      "with holes. The stonework makes you think that this " +
      "maze was crafted by minotaurs.\n");
    add_item(({"holes","tiny holes"}),
      "Tiny holes riddle the walls and floor, for what reason " +
      "you do not know. Looking through the holes in the " +
      "walls makes you think that these walls must be " +
      "at least five feet thick.\n");
    add_item("floor","The floor of the maze is riddled " +
      "with holes.\n");

    add_exit(MAZE + "c10","west",0);
    add_exit(MAZE + "c12","east",0);

    reset_flotsam_room();
}

string
long_descr()
{
    return "You stand within the great stone walls of a " +
    "complex maze. The walls and floor are riddled with " +
    "tiny holes, and through them you can hear the sound of " +
    "the sea.\n";
}
