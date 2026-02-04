inherit "/d/Terel/port/beach/beach";
#include <macros.h>

#define BEACH "/d/Terel/port/beach/"

void
create_beach()
{
    add_exit(BEACH + "b13",  "west",      0);
    add_exit(BEACH + "b7",   "north",     0);
    add_exit(BEACH + "b15",  "east",      0);
    add_exit(BEACH + "b14",  "south",     VBFC("to_sea"));
}
