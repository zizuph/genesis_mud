inherit "/d/Cirath/ak_wela/inherit/outside.c";
#include "/d/Cirath/common/defs.h"

void
create_room()
{
    set_short("Szun Moon Boulevard");
    set_long("This part of Szun Moon Boulevard lies at the very center of " +
             "Ak Wela.  The city hall lies just to the north, and a " +
             "blackened, cracked wall to your south marks the Alchemist " +
             "guild.  Just east of here is the intersection with Pou Shun " +
             "Street, and further on lie the boardwalk and the piers.  In " +
             "the distance to the west is the city's main gates.\n");

    add_item("wall", "The soot-black wall appears to have been cracked by" +
             "some great concussive force from inside.\n");

    add_exit(AK_WELA_DIR + "cityhall", "north", 0, 2);
    add_exit(AK_WELA_DIR + "szun_moon3", "east", 0, 2);
    add_exit(AK_WELA_DIR + "szun_moon5", "west", 0, 2);
}
