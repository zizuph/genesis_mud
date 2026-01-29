/* Road to Haven by Morrigan */

#include "/d/Krynn/haven/local.h"

inherit ROADBASE;

void
create_road()
{
    add_my_desc("The road to Haven continues southeast along the edge "+
      "of the mountains surrounding the dread forest of Darken Wood. "+
      "The White-Rage River cuts a swath through the plains to the "+
      "south, and you spot a bridge to the far southeast, crossing "+
      "the river and leading into the outcropping of land on which "+
      "the capital of Abanasinia rests.\n");

    add_item("bridge", "The bridge was constructed to cross the White-Rage "+
      "river, allowing access to Haven and the surrounding areas.\n");
    add_item(({"river", "white rage river", "White-Rage River", "White Rage River",
	"River"}), "The White-Rage River cuts a path across southern " +
      "Abanasinia, drawing its name from the white rapids that " +
      "seem to rage against the river banks.\n");

    add_exit(RDIR + "road7", "northwest");
    add_exit(RDIR + "road9", "southeast");

    OUTSIDE;
}

