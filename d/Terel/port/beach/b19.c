inherit "/d/Terel/port/beach/beach";
#include <macros.h>

#define BEACH "/d/Terel/port/beach/"

void
create_beach()
{
    add_exit(BEACH + "b18",  "west",      0);
    add_exit(BEACH + "b12",  "north",     0);
    add_exit(BEACH + "b19",  "south",     VBFC("to_sea"));
}
