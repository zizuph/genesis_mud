inherit "/std/room";
inherit "/d/Genesis/lib/post";

#include <stdproperties.h>

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("The post office of Gont Port");
    set_long("This is the post office in Gont "+
        "Port. From here travellers can post a message to anyone in "+
        "the world. To the west you notice an exit to a small "+
        "room, from which issue strange sounds.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_exit("harrekki_room", "west");
    add_exit("city_street/city_road31", "south");
    reset_room();
}

public void
init()
{
    ::init();
    post_init();
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob,to);
    post_leave_inv(ob, to);
}
