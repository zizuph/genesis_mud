inherit "/d/Terel/port/beach/beach";

#define BEACH "/d/Terel/port/beach/"

void
create_beach()
{
    add_exit(BEACH + "b11",  "west",      0);
    add_exit(BEACH + "b19",  "south",     0);

    add_entrance(BEACH + "cave1", "There is an entrance here.\n", 5);
}
