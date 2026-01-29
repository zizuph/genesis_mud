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
    set_long("Here the wide cobbled street takes a"+
        " turn to the southeast, continuing between stone"+
        " buildings and towers on both sides of the road."+
        " This seems to be quarters for traders, and here"+
        " and there you can see shops located at the ground"+
        " floor of the buildings. You notice a sign hanging"+
        " above an open door to the south, leading inside"+
        " one of the shops. On the other side of the street"+
        " are living quarters, with green lawns surrounding"+
        " old looking stone buildings. Beyond the buildings"+
        " you can spot the crenelated wall surrounding Gont"+
        " Port. The street is very crowded here, with people"+
        " passing by everywhere.\n");
    add_item("shops","These seem to be regular shops and"+
        " offices serving the citizens, but not of much"+
        " interest for an adventurer like you. You can enter"+
        " one of the stores to the south.\n");
    add_item("street","The cobbled street is wide"+
        " and spacious, leading between large stone buildings"+
        " and high towers to the west and southeast.\n");
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
    add_item("buildings","Tall stone buildings built"+
        " by black stone line the sides of the street,"+
        " probably homes for rich merchants and nobles"+
        " of this city. To the south you can enter an"+
        " open door with a sign hanging over it.\n");
    add_item("wall","Beyond the buildings to the north"+
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
    add_exit("city_road3", "west");
    add_exit("city_road31", "southeast");
    add_exit("../equip_shop", "south");
}

public string
sign()
{
    say(QCTNAME(this_player()) + " reads the sign.\n");
    return "The sign reads:\n"+
        "Eryndel's Equipment Shop\n\n"+
        "Best merchandise in Gont Port!\n";
}
