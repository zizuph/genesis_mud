inherit "/d/Terel/port/beach/beach";

#define BEACH "/d/Terel/port/beach/"

void
create_beach()
{
    add_exit(BEACH + "b1",   "west",      0);
    add_exit(BEACH + "b20",  "north",     0);
    add_exit(BEACH + "b3",   "east",      0);
    add_exit(BEACH + "b8",   "south",     0);
}
