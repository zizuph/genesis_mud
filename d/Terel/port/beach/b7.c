inherit "/d/Terel/port/beach/beach";

#define BEACH "/d/Terel/port/beach/"

void
create_beach()
{
    add_exit(BEACH + "b6",   "west",      0);
    add_exit(BEACH + "b1",   "north",     0);
    add_exit(BEACH + "b8",   "east",      0);
    add_exit(BEACH + "b14",  "south",     0);
}
