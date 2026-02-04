inherit "/d/Terel/port/beach/beach";

#define BEACH "/d/Terel/port/beach/"

void
create_beach()
{
    add_exit(BEACH + "b6",   "north",     0);
    add_exit(BEACH + "b14",  "east",      0);
    add_exit(BEACH + "s1",   "south",     0, 3);

    add_item(({"stone", "stones"}), "The look slippery due to " +
	     "the waves watering them every now and then.\n");

    add_my_desc("There are some stones in the sea to the south. " +
		"You can probably walk on them.\n");
}
