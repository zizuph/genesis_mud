inherit "/d/Terel/port/beach/beach";

#define BEACH "/d/Terel/port/beach/"

void
create_beach()
{
    add_exit(BEACH + "b3",   "west",      0);
    add_exit(BEACH + "b22",  "north",     0);
    add_exit(BEACH + "b5",   "east",      0);
    add_exit(BEACH + "b10",  "south",     0);
}
