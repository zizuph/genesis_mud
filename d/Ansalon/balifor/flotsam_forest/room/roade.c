#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"

inherit FOREST_OUT;

void
reset_flotsam_room()
{
    return;
}

create_flotsam_room()
{
    set_short("Between cultivated fields on an eroding dirt road");
    set_long("@@long_descr");

    add_item(({"fields","cultivated fields","fields of wheat",
	"cultivated fields of wheat","wheat"}),
      "On either side of the road are the cultivated fields of wheat " +
      "that support the populace of Flotsam.\n");
    add_item(({"shadows","forest","ancient forest","evergreen forest",
	"ancient evergreen forest"}),
      "Before you is a forboding forest. The road you are standing on " +
      "disappears into its shadows.\n");
    add_item(({"road","eroding dirt road","dirt road","eroding road"}),
      "You stand upon a wide dirt road that is slowly eroding away " +
      "due to lack of maintenance.\n");
    add_item(({"flotsam","Flotsam","town","town of flotsam"}),
      "To the north you can make out the port town of Flotsam. Rumours " +
      "have it that it is presently occupied by the Blue Dragonarmy, " +
      "for what reason you do not know.\n");

    add_exit(FROOM + "roadd","north",0);
    add_exit(FROOM + "road1","south",0);

    reset_flotsam_room();

}

string
long_descr()
{
    return "You stand upon an eroding dirt road before an ancient " +
    "forest. Its shadows swallow up the road as it plunges into the evergreen "+
    "forests depths. To the north the road continues to the town of Flotsam, " +
    "passing through cultivated fields of wheat on either " +
    "side. " + tod_descr1() + "\n";
}
