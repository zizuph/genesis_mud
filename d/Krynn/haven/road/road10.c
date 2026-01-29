/* Road to Haven by Morrigan */

#include "/d/Krynn/haven/local.h"

inherit ROADBASE;

void
create_road()
{
    add_my_desc("You now stand only a bit west of the capital of "+
      "Abanasinia and home of the Seekers, Haven. The road travels "+
      "northwest towards a bridge which crosses the White-Rage River, "+
      "and east towards Haven. You notice the dark woods of Qualinesti "+
      "to your south, across the River. Another forest rests to " +
      "the west, joining Qualinesti to the southwest. A small " +
      "encampment of dwarves is to the immediate south, here to trade "+
      "with the inhabitants of Haven from the kingdom of the Neidar in "+
      "the further south of Abanasinia.\n");

    add_item("bridge", "The bridge was constructed to cross the White-Rage "+
      "river, allowing access to Haven and the surrounding areas.\n");
    add_item(({"river", "white rage river", "White-Rage River", "White Rage River",
	"River"}), "The White-Rage River cuts a path across southern " +
      "Abanasinia, drawing its name from the white rapids that " +
      "seem to rage against the river banks.\n");

    add_exit(RDIR + "road9", "northwest", "@@bridge");
    add_exit(HROOM+"entrance","east","@@no_haven");
    add_exit(RDIR + "forest1", "west", 0, 3, 1);
    add_exit(DROOM + "entrance", "south");

    OUTSIDE;
}

int
bridge()
{
    write("You cross over the the White-Rage River on a sturdy wooden bridge "+
      "about 5 meters wide.\n");
    return 0;
}

int
no_haven()
{
    write("You head into the town of Haven.\n");
    return 0;
}

