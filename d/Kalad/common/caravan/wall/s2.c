#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_short("Wall street");
    set_long("You are walking along Wall Street in northeastern Kabal. "+
      "To the east tower the massive city walls, while crowded buildings "+
      "line the western side of the road. Animal refuse litters the ground "+
      "here.\n");
    set_time_desc("A number of people are crowded around the entrance to the "+
      "stone structure in the west.\n", "A few bedraggled people are visible "+
      "around the stone structure in the west.\n");

    add_item(({ "wall street", "street" }),
      "The road is paved in dark grey cobblestones that are worn and "+
      "slightly cracked because of heavy use. Animal refuse litters the "+
      "street.\n");

    add_item(({ "massive city walls", "city walls", "walls" }),
      "Examining the city wall closer you take note of the fine stone it "+
      "was constructed from, most likely quarried from the Hespyre mountains "+
      "just east of Kabal. The wall rises to a height of thirty feet and "+
      "stretches to the north and south.\n");

    add_item(({ "buildings" }),
      "Most of the buildings are wooden structures that look in need of "+
      "serious repair. You surmise that these buildings serve as housing for "+
      "the poorer laborers of the Caravan district. A stone structure in "+
      "the west attracts your attention, simply because its not constructed of "+
      "wood, as are the other buildings on this street.\n");

    add_item(({ "stone structure", "structure" }), "A simply-designed building, "+
      "being square in shape and rising but one story high.\n");

    add_item(({ "entrance" }), "A slightly darkened entryway leading into the "+
      "structure.\n");

    add_item(({ "people" }), "The ordinary, everyday citizens of the city-state "+
      "of Kabal.\n");

    add_item(({ "animal refuse", "refuse" }),
      "Peering more intently at the filth you distinguish the fecal remains "+
      "of both horses and oxen, as well as some other animals.\n");

    add_exit(CVAN + "wall_wayfar", "north");
    add_exit(CVAN + "wall/shrine_solara", "west");
    add_exit(CVAN + "wall/s3", "south");
}

int
block()
{
    write("The entrance appears to be blocked, there is no way past it.\n");
    return 1;
}
