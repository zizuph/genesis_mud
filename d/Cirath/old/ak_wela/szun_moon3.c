inherit "/d/Cirath/ak_wela/inherit/outside.c";
#include "/d/Cirath/common/defs.h"

void
create_room()
{
    set_short("Intersection of Szun Moon and Pou Shun");
    set_long("This is the intersection of Szun Moon Boulevard and Pou " +
             "Shun Street.  The ugly brown of Phiringy Trading's warehouse " +
             "is to the northeast, while their offices lie just north of " +
             "the city hall, which is northwest of this intersection.  " +
             "The temple lies southeast of here, and the occasional " +
             "explosions to the southwest mark the Alchemist guild hall.  " +
             "Further west you see the tower of the Astrologer's guild.  " +
             "There is a sewer grate in the middle of the street here.\n");

    add_exit(AK_WELA_DIR + "pou_shun3", "north", 0, 2);
    add_exit(AK_WELA_DIR + "pou_shun2", "south", 0, 2);
    add_exit(AK_WELA_DIR + "szun_moon2", "east", 0, 2);
    add_exit(AK_WELA_DIR + "szun_moon4", "west", 0, 2);
//  add_exit(AK_WELA_DIR + "sewer_ent1", "down", "@@check_grate", 5);
}
