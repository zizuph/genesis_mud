/* Road to Haven by Morrigan */

#include "/d/Krynn/haven/local.h"

inherit ROADBASE;

void
create_road()
{
    add_my_desc("A bridge crosses the White-Rage River to your southeast "+
      "here, leading towards Haven. To the south you spot the enchanted "+
      "woods of Qualinesti, home of the elves. Around the tip of the "+
      "mountains to your east, you can just make out the village of "+
      "Haven. You also spot some woods far to the west, at the foothills "+
      "of the now-distant Kharolis Mountains.\n");

    add_item("bridge", "The bridge was constructed to cross the White-Rage "+
      "river, allowing access to Haven and the surrounding areas.\n");
    add_item(({"river", "white rage river", "White-Rage River", "White Rage River",
	"River"}), "The White-Rage River cuts a path across southern " +
      "Abanasinia, drawing its name from the white rapids that " +
      "seem to rage against the river banks.\n");

    add_exit(RDIR + "road8", "northwest");
    add_exit(RDIR + "road10", "southeast", "@@bridge");

    OUTSIDE;
}

int
bridge()
{
    write("You cross over the the White-Rage River on a sturdy wooden bridge "+
      "about 5 meters wide.\n");
    return 0;
}
