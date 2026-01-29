#include "plains.h"

inherit PLAINBASE;

public void
create_khalakhor_room()
{
    create_plain();

    add_exit(PLAINS + "plains_38_24", "north");
    add_exit(PLAINS + "plains_39_24", "northeast");
    add_exit(PLAINS + "plains_39_25", "east");
    add_exit(PLAINS + "plains_39_26", "southeast");
    add_exit(PLAINS + "plains_37_24", "northwest");
}
