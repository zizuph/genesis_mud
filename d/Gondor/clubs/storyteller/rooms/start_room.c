/*
 * /d/Gondor/clubs/storytellers/rooms/start_room.c
 *
 * Storyteller Club startroom
 * 
 */

inherit "/d/Gondor/std/room";

#include "/d/Gondor/defs.h"
#include "../defs.h"
#include <macros.h>
#include <stdproperties.h>

public int get_key(string str);

object box;

public void reset_room()
{
    if (!box)
    {
        box = clone_object(STORYT_DIR +"obj/footlocker");
        box->move(this_object());
    }
}
public string
read_rules()
{
    return "Storytellers may begin their days here.\n";
}

public void
create_gondor()
{
    set_short("a quiet chamber");
    set_long("This quiet room is obviously for sleeping. The bunks that "+
        "line the walls look quite comfortable and clean. The room has "+
        "a doorway which leads north. A footlocker sits on the floor in "+
        "a corner of the room, above which is a small shelf. Next to the "+
        "north exit, a small sign is on the wall.\n");

    add_item(({"poster", "sign"}), &read_rules());
    add_item(({"door", "doorway", "north" }), "The doorway leads to the "+
        "hallway in the private area of the clubhouse.\n");
    add_item(({ "shelf", "small shelf"}), "The small shelf has several keys "+
        "laying on it.\n");
    add_item(({"key", "keys"}), "There are several keys here, you could "+
        "probably take one if you wanted.\n");

    add_cmd_item(({"poster", "sign"}), "read", 
        &read_rules());

    add_item(({"bunk", "bunks", "bed", "beds"}), "The bunks are quite "+
        "plush and comfortable looking. They are all made and look to "+
        "have clean linens.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_exit(STORYT_DIR + "rooms/ehallway", "north", 0, 0);   
    reset_room();
}

private int
start(string str)
{
    if (!IS_STORYTELLER(this_player()))
    {
        notify_fail("Only storytellers may sleep here.\n");
        return 0;
    }
    else if (this_player()->set_default_start_location(STORYT_DIR + 
        "rooms/start_room"))
    {
        write("You choose one of the bunks to sleep in.\n");
        return 1;
    }
    else
    {
        notify_fail("Some problem prevents you from starting here.\n" +
            "Please make a bug report.\n");
        return 0;
    }
}

public void
init()
{
    ::init();

    add_action(start, "start");
    add_action(start, "sleep");
    add_action(get_key, "get");
    add_action(get_key, "take");
    add_action(get_key, "pick");
}

public int
get_key(string str)
{
    if (str != "key")
        return 0;

    if (present("key", this_object()))
        return 0;

    if (present(KEY_ID, this_player()))
    {
        write("You already have a club key!\n");
        return 1;
    }

    clone_object(STORYT_DIR + "obj/club_key")->move(this_player());
    write("You take a key to the clubhouse from the shelf.\n");
    say(QCTNAME(this_player())+" takes a key to the clubhouse from "+
        "the shelf.\n");
    return 1;
}
