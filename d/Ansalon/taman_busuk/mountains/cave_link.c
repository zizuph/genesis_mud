#include "local.h"
#include "describe.h"

inherit MOUNTAINS_BASE;

#include <stdproperties.h>
#include <macros.h>

void
create_mountains_room()
{
    string *items = ({ VALLEY_ITEMS,
      ({ "cliff", "cliffs", "steep cliffs" }),
      "The steep cliffs form a natural barrier, " +
      "enclosing the valley on all sides.",
      ({ "crack" }),
      "The crack in the cliffs leads into darkness. It appears " +
      "as if there has been some attempts to hide it."
    });
    int i;

    setuid();
    seteuid(getuid());

    set_short(V1_S);

    set_long(VALLEY_TOD + "This is a valley in the " +
      "Taman Busuk mountain range. Tall conifers " +
      "form a forest here, and thick underbrush cover " +
      "the ground. You find yourself near the edge of " +
      "the valley, and steep cliffs form a natural " +
      "barrier. " + VALLEY_SEASON + "You notice a crack " +
      "in the cliffs to the north that you might be " +
      "able to enter.\n");

    if (LOAD_ERR(MOUNTAINS_OBJECT))
    {
	write("Bug! please report immediately...\n");
	return;
    }

    for (i = 0; i < sizeof(items); i+=2)
    {
	add_item(items[i], items[i+1]+"\n");
    }

    add_exit("","south","@@enter_map:" + MOUNTAINS_OBJECT + "|C@@", 2, 1);

    add_exit(CAVE_DIR + "cave1", "north");
}


