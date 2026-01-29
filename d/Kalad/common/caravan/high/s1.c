#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_short("High street");
    set_long("This is High Street in northern Kabal. To the west a small "+
      "road leads towards a squat gatehouse. Buildings line the western side "+
      "of High Street while to the east, a high stone wall surrounding a "+
      "massive edifice is visible. Large intersections lie to the north "+
      "and south.\n");

    add_item(({ "high street" }),
      "A wide concourse paved in cobblestones leading north out of the city, "+
      "and south deeper into Kabal's heart.\n");

    add_item(({ "small road", "road" }),
      "A small road paved in cobblestones that heads towards the local "+
      "gatehouse, where the city guards congregate.\n");

    add_item(({ "gatehouse" }),
      "A one-story stone structure that is a few dozen feet across, giving "+
      "the appearance that it is squat or low in shape.\n");

    add_item(({ "buildings" }),
      "Tidy-looking wooden structures that serve as small shops. Its most "+
      "likely they get the majority of their business from the city guards "+
      "and nobles.\n");

    add_item(({ "high stone wall", "stone wall", "wall" }),
      "It reaches fifteen feet into the air and travels in a north-south "+
      "direction completely encircling a large stone edifice. Remarkably "+
      "there is not the slightest marring of its surface, as if the wall "+
      "were newly constructed.\n");

    add_item(({ "edifice" }),
      "Little can be made out from here, since the wall encircling it blocks "+
      "out most of the building. All that can be made out is the extremely "+
      "dark stone the structure was constructed from.\n");

    add_exit(CVAN + "high-gate", "north");
    add_exit("/d/Kalad/common/noble/guards", "west", "@@block");
    add_exit(CVAN + "high-wayfar", "south");
}

int
block()
{
    write("The gatehouse is currently not open.\n");
    return 1;
}
