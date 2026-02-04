inherit "/d/Terel/port/beach/beach";
#include <macros.h>

#define BEACH "/d/Terel/port/beach/"

void
create_beach()
{
    add_exit(BEACH + "b16",  "west",      0);
    add_exit(BEACH + "b10",  "north",     0);
    add_exit(BEACH + "b18",  "east",      0);
    add_exit(BEACH + "b17",  "south",     VBFC("to_sea"));
}
