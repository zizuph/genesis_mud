inherit "/d/Terel/port/beach/beach";
#include <macros.h>

#define BEACH "/d/Terel/port/beach/"

void
create_beach()
{
    add_exit(BEACH + "b17",  "west",      0);
    add_exit(BEACH + "b11",  "north",     0);
    add_exit(BEACH + "b19",  "east",      0);
    add_exit(BEACH + "b18",  "south",     VBFC("to_sea"));
}
