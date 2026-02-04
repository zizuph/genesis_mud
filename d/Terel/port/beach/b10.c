inherit "/d/Terel/port/beach/beach";

#define BEACH "/d/Terel/port/beach/"

void
create_beach()
{
    add_exit(BEACH + "b9",   "west",      0);
    add_exit(BEACH + "b4",   "north",     0);
    add_exit(BEACH + "b11",  "east",      0);
    add_exit(BEACH + "b17",  "south",     0);
}
