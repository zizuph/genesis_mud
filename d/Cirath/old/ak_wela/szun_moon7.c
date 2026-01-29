inherit "/d/Cirath/ak_wela/inherit/outside.c";
#include "/d/Cirath/common/defs.h"

void
create_room()
{
    set_short("Szun Moon Boulevard");
    set_long("West, Szun Moon approaches the gates, and you can see the " +
             "guards there carefully appraising all travellers into the city. " +
             "Eastwards, the street continues past Silk street and Pou shun " +
             "street, to the docks. North, a lavishly decorated house lies, " +
             "with ornate carvings adorning the walls, through which iron barred " +
             "windows you can glimpse some rare jewels. This is the shop of " +
             "Mangodi, the local jeweller. South an obscure shop can be seen, " +
             "with some plants and pouches visible through the open doorway.\n");

    add_exit(AK_WELA_DIR + "jewellers", "north", 0, 2);
    add_exit(AK_WELA_DIR + "szun_moon6", "east", 0, 2);
    add_exit(AK_WELA_DIR + "szun_moon8", "west", 0, 2);
    add_exit(AK_WELA_DIR + "herbalist","south", 0, 2);
}
