#include "default.h"
inherit CVAN_ROOM;

object ob1;

void reset_room();

void
create_cvan_room()
{
    set_short("Intersection of Alley and Wayfarer");
    set_long("This is a small intersection between Wayfarer Boulevard "+
      "and the much smaller Cargo Alley, which lies to the north of "+
      "here.  The road north, although smaller than Wayfarer Boulevard "+
      "looks to be well-travelled. "+
      "Looking further west you can see where Wayfarer Boulevard intersects "+
      "with the Street of Chains. "+
      "However, what really catches your attention is the towering edifice "+
      "to the northwest, you can't see too many details because there is a "+
      "high stone wall blocking your lower view of the building. "+
      "There are large piles of animal refuse towards the north.\n");

    add_item( ({ "edifice", "building" }),
      "From what you can see from here, the building has to be at least 4 "+
      "stories in height, perhaps even 5. The only details you can pick "+
      "out are the dark grey,almost black stones the edifice is "+
      "constructed from. Compared to the other buildings in this area, the edifice is "+
      "positively gargantuan!\n");

    add_item( ({ "stone wall", "wall" }),
      "This is a smooth stone wall, with absolutely no graffiti marks "+
      "visible anywhere on it's surface. It looks to be at least fifteen "+
      "feet high, and very, very solid.\n");

    add_item( ({ "intersection", "road" }),
      "This is a small T-intersection, you can see that Wayfarer "+
      "Boulevard is paved in grey cobblestones while Cargo Alley is "+
      "mostly hard-packed earth.\n");

    add_item( ({ "piles", "refuse" }),
      "These are unusually large piles of dung, some piles are so high "+
      "that they are taller than a full-grown hobbit!\n");

    add_exit(CVAN + "wayfar/s2", "east");
    add_exit(CVAN + "alley/s1", "north");
    add_exit(CVAN + "chains_wayfar", "west");

    reset_room();
}

void
reset_room()
{
    if (!ob1)
    {
	ob1 = clone_object(NPC + "cmilitia");
	ob1->move_living("M", TO);
    }
}
