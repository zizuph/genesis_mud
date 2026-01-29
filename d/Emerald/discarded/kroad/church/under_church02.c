#include "defs.h"

inherit GRAVEYARD_DIR + "under_church_hall";

void
create_hall()
{
    add_exit("under_church01", "east");
    add_exit("under_church03", "west");
}
