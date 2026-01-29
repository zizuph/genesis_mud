#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>

#include <macros.h>

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Wide crowded street");
    set_long("Stone buildings and towers line the road"+
        " on both sides as it continues southwards, following"+
        " the crenelated wall as it turns. This seems to be"+
        " merchant quarters, dominated by large stone"+
        " buildings owned by trading companies each with its"+
        " own symbol or banner above the doors. Older looking"+
        " stone buildings are built on the north side of the"+
        " road, embedded in green ivy and surrounded by"+
        " gardens. One of the stone buildings to the east"+
        " has a white flag flapping from the roof and a"+
        " sign over the door. Just to the north is a small"+
        " stone building with the words Post Office engraved above"+
        " the entrance. The street is crowded here,"+
        " both with common people and merchants dressed"+
        " in expensive clothes.\n");
    add_item("flag","Above the stone building to the"+
        " east you can see the white flag of the Lord of"+
        " Gont flapping gently in the breeze.\n");
    add_item("east building","The building to the east"+
        " seems to house some sort of official servive,"+
        " judging by the white flag of the Lord of Gont"+
        " flapping from a pole on top of the roof. You"+
        " can enter it through wide open doors.\n");
    add_item("north building", "The small stone building "+
        "to the north has the words Post Office engraved over "+
        "the entrance. There seems to be a window on the west side "+
        "of it, where carrier pigeons come and go.\n");
    add_item("street","The cobbled street is wide"+
        " and spacious, leading between large stone buildings"+
        " and high towers to the northeast and south.\n");
    add_item("towers","Several high towers where rich"+
        " merchants and nobles live stand on each side of"+
        " the road. Some distance to the west you can spot"+
        " a wider tower, with the white flag of the Lord of"+
        " Gont flying above it.\n");
    add_item("west tower","This tower is wider than the"+
        " others and has the white flag of the Lord of Gont"+
        " flying over it.\n");
    add_item("people","You can see many citizens and"+
        " travelers passing by on each side. Most of them"+
        " are dark-skinned, born on Gont island but you can"+
        " also see other people dressed in exotic clothes"+
        " coming from different places all over the"+
        " Archipelago to trade or for adventure.\n");
    add_item("merchants","On this street you can"+
        " see many merchants, dressed in expensive clothes"+
        " walk between the trading companies and try to strike"+
        " a good deal for the goods they brought.\n");
    add_item(({"companies","buildings"}),
        "Most of the stone buildings"+
        " are at least three storys high, and are elaborately"+
        " decorated with masonry. This is where the trading"+
        " companies of Gont Port have their offices, and you"+
        " can see their different emblems and banners hanging"+
        " above the door.\n");
    add_item("wall","Beyond the buildings to the north"+
        " and east"+
        " you can see the high crenelated wall, surrounding"+
        " the whole city.\n");
    add_item("gardens","Well-tended grass lawns with bushes"+
        " and flowerbeds surround some of the older-looking"+
        " stone buildings on the north side of the street."+
        " Green ivy climb up the stone walls, making the"+
        " buildings look more homely. These houses are"+
        " probably homes for wealthier merchants.\n");
    add_item("sign", "@@sign");
    add_cmd_item("sign", "read", "@@sign");
    add_exit("city_road32", "northwest");
    add_exit("city_road30", "south");
    add_exit("../post_office", "north");
    add_exit("../bank", "east");
}

public string
sign()
{
    say(QCTNAME(this_player()) + " reads the sign.\n");
    return "The sign reads:\nThe Bank of Gont Port.\n";
}
