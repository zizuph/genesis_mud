#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>

#define COBBLED_ROAD "/d/Earthsea/gont/tenalders/south_path/cobbled_road1"

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Outside the Port of Gont");
    set_long("You are standing"+
        " before the landbridge leading"+
        " across the moat into the great Port of Gont, well"+
        " protected inside the thick city walls surrounding it."+
        " Above the"+
        " walls rise high buildings and towers, all built in"+
        " cut stone and over the higher towers flaps brightly"+
        " coloured flags in the wind. Two very large, carved dragons stand"+
        " on each side of the narrow landbridge, giving you the"+
        " impression of stern guards on post.\n");
    add_item("moat","A deep moat, filled with sea water is"+
        " dug around the whole city. The water seems to be"+
        " in a constant circling movement, driven by the large"+
        " waves rolling in from the sea outside.\n");
    add_item("walls","The high walls rises just inside the"+
        " moat, giving effective protection from Kargs and"+
        " other possible attackers. Behind the landbridge, you"+
        " can see a wide gate passing through an arch of stone,"+
        " into the city.\n");
    add_item(({"towers","houses"}),"Tall houses and towers"+
        " are visible behind the mighty walls, built by cut"+
        " stone.\n");
    add_item("flags","Flags in many different colours fly"+
        " over the higher towers. Above the highest tower"+
        " you can see the white flag of the Lord of Gont.\n");
    add_item("landbridge","The road leads over the"+
        " narrow landbridge disappearing through a tall arch"+
        " in the city walls.\n");
    add_item("dragons","These dragons, delicately carved"+
        " by white stone with great detail are very true to life."+
        " They look like stern guards"+
        " come alive any minute. They look like stern guards,"+
        " taking a post on each side of the land bridge.\n");
    add_exit(COBBLED_ROAD, "north");
    add_exit("landbridge", "south");
}
