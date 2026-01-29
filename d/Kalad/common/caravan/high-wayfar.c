#include "default.h"
inherit CVAN_ROOM;

object aylmer;

void reset_room();

void
create_cvan_room()
{
    set_short("Intersection of High and Wayfarer");
    set_long("You've just reached the huge intersection between High "+
      "Street and Wayfarer Boulevard. From here, you can head west along "+
      "Wayfarer Boulevard into the Upper Class district, residence of the "+
      "wealthy nobles of Kabal. High Street which travels north-south can "+
      "be followed south, where it heads deeper into the heart of the city. "+
      "Heading north along High Street eventually leads to the highland "+
      "gate, an exit from Kabal leading to the expansive estates of the "+
      "nobles. Many buildings crowd the intersection, "+
      "except to the southwest along a small street. There the buildings "+
      "are replaced by a large group of trees, a veritable forest within "+
      "Kabal, the nobles' park. Visible to the northeast, past high stone "+
      "walls is a massive edifice.\n");

    add_item(({ "intersection" }),
      "Three roads cross through this point, you see that each of the roads "+
      "is paved in slate-grey cobblestones and despite being heavily "+
      "travelled are in relatively good shape, being only slightly worn "+
      "down.\n");

    add_item(({ "buildings" }),
      "Examining the wooden buildings closer you see that they are made "+
      "from the mighty redwoods that grow on the slopes of the Hespyre "+
      "mountains. As such, these structures were built to last, showing "+
      "little wear from the harsh effects of time and weather.\n");

    add_item(({ "trees", "forest", "park" }),
      "Looking more intently at the shadow-filled woods, it strikes you as "+
      "the perfect haven for thieves, murderers and other brigands, since "+
      "capture would prove to be more difficult there.\n");

    add_item(({ "high stone walls", "walls" }),
      "It seems to enclose a large stone edifice, due to the extreme height "+
      "of the wall, around fifteen feet, you can only glimpse the very top "+
      "of the structure. Another interesting fact about the wall is that "+
      "not one mark or stain is visible on its surface, as if it had just "+
      "been newly constructed.\n");

    add_item(({ "edifice" }),
      "Little detail can be made from this point, all you can tell is that "+
      "the structure is made of some extremely dark stone.\n");

    add_exit(NOBLE + "road/r16", "southwest", 0);
    add_exit(NOBLE + "wayfarer/s11", "west", 0);

    add_exit(CVAN + "high/s1", "north");
    add_exit(CVAN + "wayfar/s1", "east");
    add_exit(CVAN + "high/s2", "south");

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

int
block()
{
    write("The way is blocked by a barricade.\n");
    return 1;
}
