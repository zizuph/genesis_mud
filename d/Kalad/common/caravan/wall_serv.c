#include "default.h"
inherit CVAN_ROOM;

object ob1;

void reset_room();

void
create_cvan_room()
{
    set_short("Intersection of Wall and Servant");
    set_long("This point is where the cobblestoned Wall Street intersects "+
      "with the dirt-covered Servant Street. Wall street follows the massive "+
      "city walls of Kabal to the north and south while Servant Street heads "+
      "west from here. Many crowded buildings line both streets, though the "+
      "ones along Servant Street look in poorer condition than those aside "+
      "Wall Street. All manner of refuse litter the intersection.\n");

    add_item(({ "massive city walls", "city walls", "walls" }),
      "The finely crafted and sturdily built city walls stretch to the north "+
      "and south and stand some thirty feet tall.\n");

    add_item(({ "crowded buildings", "buildings" }),
      "Almost all of the buildings you can see are made of wood and look in "+
      "need of bad repair, however the structures along Servant Street look  "+
      "even worse, many appearing as if they might collapse at any moment.\n");

    add_item(({ "refuse" }),
      "A variety of trash can be seen, bits and pieces of scrap metal, feces "+
      "from the many animals that travel Wall Street, and even a few homeless "+
      "sleeping in the gutters.\n");

    add_exit(CVAN + "beggar_serv", "west");
    add_exit(CVAN + "wall/s3", "north");
    add_exit(CVAN + "wall_warehouse", "south");

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
