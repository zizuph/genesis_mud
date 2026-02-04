inherit "/d/Terel/port/beach/beach";

#define BEACH "/d/Terel/port/beach/"

void
create_beach()
{
    add_exit(BEACH + "b8",   "west",      0);
    add_exit(BEACH + "b3",   "north",     0);
    add_exit(BEACH + "b10",  "east",      0);
    add_exit(BEACH + "b16",  "south",     0);
}
