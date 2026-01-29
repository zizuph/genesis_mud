#include "default.h"
inherit CVAN_ROOM;

object aylmer;

void reset_room();

void
create_cvan_room()
{
    set_short("Intersection of High and Servant");
    set_long("This t-intersection is where the heavily travelled High "+
      "Street is met by Servant Street, a narrow and cramped roadway by "+
      "comparison. High Street which heads north and south from here is "+
      "bordered on the west by a dense group of trees, a park in the "+
      "adjacent Upper Class district. Buildings line the eastern side of "+
      "High Street.\n");

    add_item(({ "high street" }),
      "A wide concourse paved in slate-grey cobblestones that appear "+
      "worn and slightly cracked from heavy traffic, although still in good "+
      "shape for such a busy road.\n");

    add_item(({ "servant street", "roadway" }),
      "It appears to have once been paved in cobblestones, now however all that "+
      "is left of the pavement are a few fragments of rock, partially "+
      "buried in the dirt that now makes up most of the street.\n");

    add_item(({ "trees", "park" }),
      "A shadow-filled and dense pack of trees. It strikes you as a good "+
      "place for thieves, muggers and other criminals to hide in.\n");

    add_item(({ "buildings" }),
      "Tidy-looking wooden buildings that line the eastern side of High "+
      "Street. This seems like a middle-class area of the city, where "+
      "the occupants have enough money to live without want, but not enough "+
      "to live in comfort.\n");

    add_exit(CVAN + "high/s3", "north");
    add_exit(CVAN + "servant/s1", "east");
    add_exit(CVAN + "high/s4", "south");

    reset_room();
}

void
reset_room()
{
    if(!objectp(aylmer))
    {
	seteuid(getuid(this_object()));
	aylmer = clone_object(NPC + "cmilitia");
	aylmer->move(this_object());
    }
}
