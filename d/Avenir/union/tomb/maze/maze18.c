#include "../defs.h"
inherit (MAZE + "maze");

public void
create_maze(void)
{
    set_long(::query_long()[..-2] + " Leading down into the center of the "+
	"floor, circled by a narrow border of smooth grey stone, "+
	"a set of stairs descends into a bright room below.\n");

    add_exit("sphere", "down");
}
