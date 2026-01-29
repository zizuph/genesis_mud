#include "default.h"
inherit CVAN_ROOM;

object ob1;

void reset_room();

void
create_cvan_room()
{
    set_short("Intersection of Caravan and Servant");
    set_long("You are now at the intersection of Caravan and Servant "+
      "streets. Gazing to your east and west you can't help but notice "+
      "the marked differences between the two roads. While Caravan street "+
      "is broad to allow greater amounts of traffic to enter and leave "+
      "Kabal, Servant street is relatively narrow and cramped, insuring "+
      "that little traffic, besides local, need look upon the poverty - "+
      "stricken buildings that line it. "+
      "At the corner in Caravan Lot, a large muddy field, you can see "+
      "the crowded stalls where travelling merchants and their animals "+
      "reside.\n");

    add_item( ({ "buildings" }),
      "The buildings along Caravan street all look respectable while "+
      "those along Servant street are small, and shabby.\n");

    add_item( ({ "street", "streets" }),
      "Caravan street is paved with cobblestones, a few of which seem "+
      "loose, Servant street however is for the most part a gravel road "+
      "with the only paved section near to this intersection.\n");

    add_exit(CVAN + "caravan/s3", "northeast");
    add_exit(CVAN + "servant/s3", "west");
    add_exit(CVAN + "caravan/s4", "southwest");
    add_exit(CVAN + "servant/s4", "east");

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
