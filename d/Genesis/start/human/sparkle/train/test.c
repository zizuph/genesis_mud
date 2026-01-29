/* test room for calling up item descs from another file */

#pragma strict_types

inherit "/std/room.c";

#include <macros.h>
#include <stdproperties.h>

string medusa_desc();

public void
create_room()
{
    set_short(" gloomy dungeon");
    set_long("A gloomy dungeon deep in an underground catacomb. There" +
      " is only one exit, a flight of stairs going down.\n");

    add_item(({"medusa","medusa head"}), "@@medusa_desc");

    add_exit("catacomb2", "down", 0, 1);

    reset_room();
}

string
medusa_desc()
{
    cat("/d/Genesis/start/human/sparkle/obj/pics/medusa.pic");
    return "";
}
