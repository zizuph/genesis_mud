inherit "/d/Terel/port/beach/beach";

#define BEACH "/d/Terel/port/beach/"

void
create_beach()
{
    add_exit(BEACH + "b2",   "west",      0);
    add_exit(BEACH + "b21",  "north",     0);
    add_exit(BEACH + "b4",   "east",      0);
    add_exit(BEACH + "b9",   "south",     0);
}
