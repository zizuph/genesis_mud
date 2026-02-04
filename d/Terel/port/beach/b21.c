inherit "/d/Terel/port/beach/beach";

#define BEACH "/d/Terel/port/beach/"

void
create_beach()
{
    add_exit(BEACH + "b20",  "west",      0);
    add_exit(BEACH + "b22",  "east",      0);
    add_exit(BEACH + "b3",   "south",     0);
}
