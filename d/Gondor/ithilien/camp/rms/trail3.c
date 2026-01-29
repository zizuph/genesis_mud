
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include "/d/Gondor/defs.h"
#include "../defs.h"


public void create_gondor();

public void
create_gondor()
{
    set_short("a curious clearing");
    set_long("This small clearing in the woods looks quite " +
      "curious.  " +
      "The trees provide a little protection from the " +
      "elements, but the ground is far from comforting.  " +
      "There are bloodstains splattered about, and " +
      "many strange footprints.  " +
      "\n");

    add_item("ground","The ground is covered with grass, " +
      "but tainted with blood spots.\n");
    add_item(({"blood","blood spots","blood stains",
	"bloodstains","bloodspots"}),
      "The blood in the area is scattered in a random " +
      "pattern, seeming to indicate a violent " +
      "fight.\n");
    add_item(({"tree","trees"}),"The trees here are not as " +
      "thick as in some areas of the woods, but still " +
      "stand tall and strong.\n");
    add_item("footprints","They seem to have been covered up " +
      "somewhat, and while you are not sure which way they lead, " +
      "you are positive they do not lead to the west.\n");

    add_exit(CAMP_ROOM_DIR + "trail2","west");
    add_exit(CAMP_ROOM_DIR + "trail5","south",0,1,1);

}
