inherit "/d/Cirath/ak_wela/inherit/outside.c";
#include "/d/Cirath/common/defs.h"

void
create_room()
{
    set_short("Szun Moon Boulevard / Silk Street Crossing");
    set_long("This large boulevard runs east-west through the very heart of the " +
             "city.  To your north, you see a smaller street heading in between " +
             "two structurse. This is Silk street, which heads far north in the city.  " +
             "Along its northern route you can find the park, and some shops. " +
             "Southwards it leads toward the sea, passing a few houses on the way. " +
             "Szun Moon continues east toward the docks, and westwards it " +
             "leads towards the gate leading out of the city.\n");
    add_exit(AK_WELA_DIR + "silk_street11", "north", 0, 2);
    add_exit(AK_WELA_DIR + "szun_moon5", "east", 0, 2);
    add_exit(AK_WELA_DIR + "szun_moon6", "west", 0, 2); 
    add_exit(AK_WELA_DIR + "silk_street13","south",0,2);
} 
