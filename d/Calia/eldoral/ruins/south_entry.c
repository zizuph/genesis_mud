#include "defs.h"

inherit STDROOM;

void
create_room()
{
    set_short("archway in southern ruins of " +
        CASTLE_NAME);
    set_long("To the north rise the crumbling ruins " +
        "of "+CASTLE_NAME+", still a creation of " +
        "beauty despite its descent into decay. " +
        "Out of an ancient forest rises the " +
        "monolithic ghost from the past, its " +
        "crumbling walls struggling eternally " +
        "against the destructive march of time. All " +
        "around you " +
        "save the north rise magnificent trees, " +
        "very old, but their beauty touched not in " +
        "the least. With the sole exception of the " +
        "archway which passes through the wall to " +
        "the north, the only way to go here appears " +
        "to be into the forest.\n\n");

    add_item(({"ruins", "Castle Chimera"}),
        "The ruins are massive, and comprised of crumbling " +
        "grey stone. You can't see much from here except " +
        "the wall, but the top of the wall is almost high " +
        "enough to be concealed by the mist, and it " +
        "extends away to the east much further than you " +
        "see.\n");
    add_item(({"forest", "trees"}),
        "All around you, except to the north, massive " +
        "firs and pines soar into the mist-filled sky.\n");
    add_item(({"archway"}),
        "A lone, partially collapsed, archway, stands " +
        "open to the north, the only apparent way beyond " +
        "the outer wall of the ruins.\n");

    add_exit(RUIN + "in_south_arch", "north");
    add_exit(FOREST + "s_forest_2", "east");
    add_exit(FOREST + "s_forest_9", "south");
    add_exit(FOREST + "s_forest_1", "west");
}
