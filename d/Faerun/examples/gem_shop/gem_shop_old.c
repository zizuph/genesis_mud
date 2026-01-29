/*
 * Herbalist and shop example
 * Finwe, September 2016
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include <macros.h>
#include <money.h>
#include <stdproperties.h>
#include <terrain.h>

inherit FAERUN_INDOORS_BASE;
inherit "/d/Genesis/gems/gem_shop";
//inherit "/d/Shire/lib/box_list";
// inherit "/lib/shop";
// inherit "/d/Faerun/lib/shop_list";

#define PATH_NAME "/d/Faerun/examples/gem_shop/"
#define STORE_ROOM (PATH_NAME + "gem_store_room")

static object gemist_npc;

void
create_indoor_room()
{
    set_short("inside a gem shop");
    set_extraline("This is the interior of the gem shop. Glass cases hold the " +
        "gems for sale.");
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);

    set_room_tell_time(300);
    add_room_tell("The lamp swings overhead, casting shadows around the room.");

    reset_faerun_room();
}

void
reset_faerun_room()
{

    if (!gemist_npc)
        gemist_npc = clone_object(PATH_NAME + "gemist");
    if (!present(gemist_npc,this_object()))
        gemist_npc->move(this_object());

}

void
init()
{
    ::init();
    init_gem_shop();
}

int
block_room()
{
    if (this_player()->query_wiz_level()) return 0;

    write("You cannot go there yet.\n");
    return 1;
}

public mixed
check_keeper()
{
    if (!gemist_npc || !present(gemist_npc))
    {
        notify_fail("The Gemist is gone. He must have " +
            "left without locking the door!\n");
        return 1;
    }
}

