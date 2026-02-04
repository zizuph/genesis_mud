inherit "/d/Terel/port/beach/beach";

#define BEACH "/d/Terel/port/beach/"

void
create_beach()
{
    add_exit(BEACH + "b7",   "west",      0);
    add_exit(BEACH + "b2",   "north",     0);
    add_exit(BEACH + "b9",   "east",      0);
    add_exit(BEACH + "b15",  "south",     0);
}
