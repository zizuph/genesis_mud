inherit "/d/Terel/port/beach/beach";

#define BEACH "/d/Terel/port/beach/"

void
create_beach()
{
    add_exit(BEACH + "b10",  "west",      0);
    add_exit(BEACH + "b5",   "north",     0);
    add_exit(BEACH + "b12",  "east",      0);
    add_exit(BEACH + "b18",  "south",     0);
}
