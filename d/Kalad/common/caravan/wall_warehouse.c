#include "default.h"
inherit CVAN_ROOM;

object ob1;

void reset_room();

void
create_cvan_room()
{
    set_short("Intersection of Wall and Warehouse");
    set_long("This large intersection is where Wall Street, which travels "+
      "north-south meets with Warehouse Lane, which heads west from here. "+
      "Towering to the east are the massive city walls of Kabal. Many crowded "+
      "buildings line the roadway to the north and south. Refuse litters the "+
      "ground here.\n");

    add_item(({ "intersection", "roadway" }),
      "Wall Street is paved with dark grey cobblestones that show the effects "+
      "of heavy usage, appearing worn down and slightly cracked. However, it "+
      "is in good shape for being such a heavily travelled road. Warehouse "+
      "Lane on the other hand appears to be nothing more than a large dirt "+
      "pathway.\n");

    add_item(({ "massive city walls", "city walls", "walls" }),
      "Examining the walls closer you note the finely crafted stone it was "+
      "built from. Clearly the stone was mined from the great Hespyre "+
      "mountains, which lie east of Kabal. The walls themself rise up thirty "+
      "feet into the air, posing a significant obstacle to any invading "+
      "forces.\n");

    add_item(({ "buildings" }),
      "All the buildings visible are made of wood. They appear a bit "+
      "weatherworn but are in fairly good condition. Looking northward you "+
      "note that they appear more crowded there.\n");

    add_item(({ "refuse" }),
      "All manner of trash is visible here, varying from odd bits of scrap "+
      "metal and useless pieces of wood to a large number of animal "+
      "droppings.\n");

    add_exit(CVAN + "wall_serv", "north");
    add_exit(CVAN + "warehouse/s4", "west");
    add_exit(CVAN + "wall-harvest", "south");

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
