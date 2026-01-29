#include "default.h"
inherit CVAN_ROOM;

object ob1;

void reset_room();

void
create_cvan_room()
{
    set_short("Intersection of Wall and Gateway");
    set_long("This is the meeting point of Wall Street and Gateway Lane. "+
      "Wall Street stretches into the distance far to the south while "+
      "Gateway Lane heads westward along the northern city walls of Kabal. "+
      "Many crowded buildings can be seen lining the side of both streets. "+
      "Also, to the northeast, a squat grey tower rises into the air.\n");

    add_item(({ "walls", "city walls" }),
      "These finely crafted walls, made from the finest stone, encircle the "+
      "entire city of Kabal.\n");

    add_item(({ "buildings" }),
      "There are many wooden edifices lining the streets. You surmise that "+
      "they serve as housing for the city guards and other workers of this "+
      "district.\n");

    add_item(({ "tower", "grey tower", "squat grey tower" }),
      "Looking up at the tower you see that it rises another fifteen feet "+
      "above the city walls, putting its total height to forty-five feet. "+
      "At the top, you can see crested stone battlements upon which city "+
      "guards keep diligent watch.\n");

    add_exit(CVAN + "gateway/s6", "west");
    add_exit(CVAN + "wall/s1", "south");
    add_exit(CVAN + "gateway/tower1", "in");

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
