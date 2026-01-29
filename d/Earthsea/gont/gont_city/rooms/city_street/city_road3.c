#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>

#define SIGN_TXT "The sign reads:\n\n     Gont Port General Store\n"

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Street southeast of the gate");
    set_long("The wide cobbled street leads to the"+
        " east and northwest between large stone buildings"+
        " and towers. To the northwest you can see the wide"+
        " gate leading inside Gont Port standing wide open"+
        " with people and carts passing in and out. Just"+
        " behind one of the stone towers to the north is"+
        " the tall crenelated wall surrounding the city."+
        " To the west is a higher tower with a white flag"+
        " flapping above the roof, but you can't see any"+
        " entrance to it from this side."+
        " Just to the south of here is an entrance into"+
        " a shop, which has a small sign over the door."+
        " This is a very busy street with people passing"+
        " by on both sides, laughing and talking loudly.\n");
    add_item("flag","The white flag is the official"+
        " symbol of the Lord of Gont.\n");
    add_item("street","The cobbled street is wide"+
        " and spacious, leading between large stone buildings"+
        " and high towers to the east and northwest.\n");
    add_item("towers","Several high towers where rich"+
        " merchants and nobles live stand on each side of"+
        " the road. To the west is a wider tower with the"+
        " white flag of the Lord of Gont flying over it.\n");
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
        " of this city.\n");
    add_item("wall","Behind a tower to the northeast"+
        " you can see the high crenelated wall, surrounding"+
        " the whole city.\n");
    add_item((({"sign", "small sign"})), SIGN_TXT);
    add_exit("city_road1", "northwest");
    add_exit("city_road32", "east");
    add_exit("../general_shop", "south");
}

public int
read_sign(string str)
{
    if(str == "sign" || str == "small sign")
    {
        write(SIGN_TXT);
        return 1;
    }

    return notify_fail("Read what?\n");
}

public void
init()
{
    ::init();
    add_action(read_sign, "read");
}
