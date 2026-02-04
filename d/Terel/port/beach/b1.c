inherit "/d/Terel/port/beach/beach";

#define BEACH "/d/Terel/port/beach/"

void
create_beach()
{
    add_exit(BEACH + "path", "northwest", 0);
    add_exit(BEACH + "b2",   "east",      0);
    add_exit(BEACH + "b7",   "south",     0);
}
