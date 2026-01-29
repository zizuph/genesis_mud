#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit KEN_OUT;

void
reset_kendermore_room()
{
    return;
}

create_kendermore_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"wooden platform","platform"}),
      "A sturdy wooden platform has been fashioned here " +
      "high up in the oak tree. From here you can go east into " +
      "a cubby house or northwest or southwest along two large " +
      "branches.\n");
    add_item(({"giant oak tree","oak tree","tree"}),
      "You stand high up in a giant oak tree. From here " +
      "you can examine the lands around you.\n");
    add_item("branches","The branches here sway silently to " +
      "a refreshing wind that blows from the north.\n");
    add_item(({"view","land","lands"}),
      "Ah there is so much to examine! Try examining to the " +
      "north, south, east or west.\n");
    add_item("north","To your north the forest extends out to the " +
      "distant coastline, where a port town lies like a broken " +
      "vessel. Further out to sea you see the " +
      "gathering of storm clouds.\n");
    add_item("west","Far out to the west the forest extends beyond " +
      "your line of vision. You notice a dark patch of forest in that " +
      "direction... probably cursed or enchanted, a perfect place for " +
      "a kender to explore!\n");
    add_item("south","To the south the ends at the border " +
      "of an expansive and desolate steppe. " +
      "You doubt any would live there, although you do notice " +
      "someone has lit a campfire there, sending " +
      "a barely noticeable trail of smoke into the air.\n");
    add_item("east",
      "To your east the forest extends to the kender " +
      "capital, Kendermore!\n");
    add_item(({"cubby house","house"}),
      "To your east is a kender cubby house, built " +
      "for the curious kender.\n");
    add_item("large branches","There are two large branches " +
      "you can travel along. One to the northwest, one to the " +
      "southwest.\n");
    add_item("hollow","You can go down through the hollow " +
      "to the base of the tree by simply going down.\n");

    add_exit(KROOM + "cubby","east",0);
    add_exit(KROOM + "board","northwest",0);
    add_exit(KROOM + "sleep","southwest","@@only_kender");
    add_exit(KROOM + "r2","down",0);

    reset_kendermore_room();
}

int
only_kender()
{
    if(TP->query_race_name() != "kender")
    {
	write("Hmm, you don't think you are curious " +
	  "enough to risk breaking your neck by walking " +
	  "along that branch.\n");
	return 1;
    }
    return 0;
}

string
short_descr()
{
    return "Standing on a platform supported by the branches " +
    "of a giant oak tree";
}

string
long_descr()
{
    return "You are standing high up on a wooden platform " +
    "supported by the branches of a giant oak tree. A refreshing wind blows " +
    "from the north, sending the branches around you " +
    "swaying while the leaves silently chatter to themselves. " +
    "As this oak towers over all the other trees in the forest, you " +
    "are granted an amazing view of all the land around you. " +
    "To your east stands a small cubby house, while two large " +
    "branches lead off the platform to your northwest " +
    "and southwest. You can also climb down through a hollow " +
    "to the ground level.\n";
}
