#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_short("Wall street");
    set_long("You are walking along Wall Street in northeastern Kabal. To "+
      "the east lie the massive walls that encircle the city, while west of "+
      "you, many crowded buildings can be seen. Animal refuse litters the ground "+
      "here.\n");

    add_item(({ "wall street", "street" }),
      "The road is paved in worn and slightly cracked cobblestones that look "+
      "in need of serious repair. The street travels north and south from "+
      "this point.\n");

    add_item(({ "massive city walls", "city walls", "walls" }),
      "Looking closer you note the fine quality of the stone used to build "+
      "the city walls, such fine quality stone can only come from the "+
      "Hespyre mountains, which lie east of Kabal. The walls rise to a height "+
      "of thirty feet.\n");

    add_item(({ "crowded buildings", "buildings" }),
      "Most of the structures are made of wood and look in need of serious "+
      "repair. You surmise that these buildings serve as housing for the "+
      "poorer workers of this district.\n");

    add_item(({ "animal refuse", "refuse" }),
      "Wrinkling your nose in disgust you press your face closer to the "+
      "animal feces in an attempt to examine them further. Before you wretch "+
      "you make out the feces of horses and oxen.\n");

    add_exit(CVAN + "wall/s2", "north");
    add_exit(CVAN + "wall_serv", "south");
}
