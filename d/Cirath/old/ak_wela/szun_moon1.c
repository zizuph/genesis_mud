inherit "/d/Cirath/ak_wela/inherit/outside.c";
#include "/d/Cirath/common/defs.h"

void
create_room()
{
    set_short("Szun Moon Boulevard");
    set_long("This large thoroughfare runs through the very heart of the " +
             "city.  To your north, you see the corporate headquarters " +
             "of Phiringy Trading, the foremost importer/exporter " +
             "in all the lands of Genesis.  The sturdy wall of their " +
             "warehouse blocks the view to the south.  A beggar sits " +
             "with his back to the wall, crying, " +
             "\"Alms for the poor!  Please, I beg of thee, just a copper!\"  " +
             "East of here is the boardwalk, and beyond that the docks.  " +
             "A short ways westward rises a tall, triangular building, " +
             "with a shorter pagodah just beyond that.  Further on, the " +
             "street eventually leaves the city.\n");
    add_exit(AK_WELA_DIR + "traders", "north", 0, 2);
    add_exit(AK_WELA_DIR + "brdwlk5", "east", 0, 2);
    add_exit(AK_WELA_DIR + "szun_moon2", "west", 0, 2);
}
