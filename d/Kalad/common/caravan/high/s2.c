#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_short("High street");
    set_long("You are travelling along High Street, a wide concourse "+
      "paved in cobblestones that stretches to the north and south. To the "+
      "west, a large group of trees, a park in the neighboring Upper Class "+
      "district can be seen. Along the eastern side of the roadway are "+
      "several buildings. A large intersection lies to the north.\n");

    add_item(({ "high street", "concourse", "roadway" }),
      "The street is paved in cobblestones that are worn and slightly "+
      "cracked, but in relatively good shape for such a busy road.\n");

    add_item(({ "trees", "park" }),
      "Examing the shadow-filled depths of the small forest, you get the "+
      "impression that it would make a perfect haven for thieves and other "+
      "brigands.\n");

    add_item(({ "buildings" }),
      "Tidy-looking wooden structures. This area appears to be a middle-class "+
      "section of Kabal, where the residents have enough money to not go "+
      "without want, but not enough to live in comfort.\n");

    add_exit(CVAN + "high-wayfar", "north");
    add_exit(CVAN + "high/s3", "south");
}
