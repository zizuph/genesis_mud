inherit "/std/room";
inherit "/d/Shire/std/room/room_tell";
#include <stdproperties.h>
#include <std.h>
#include <composite.h>
#include <filter_funs.h>
#include "/d/Shire/sys/defs.h" 

inherit "/d/Gondor/common/lib/drink_water.c";

void
create_room()
{
    setuid();
    seteuid(getuid());

    set_short("A grassy meadow");

    set_long("This is a large grassy meadow, The grass is a deep green and " +
        "thick. Wild flowers grow scattered in the meadow, dotting the " +
        "grass with vibrant colors. A small brook runs through the meadow " +
        "and into a pond.\n");

    set_room_tell_time(15);
    add_room_tell("A fish leaps out of the pond, and falls back into the water.");
    add_room_tell("Bugs skate across the pond's surface.");
    add_room_tell("A frog goes rbbt ... rbbt");
    add_room_tell("The grass waves in the breeze.");
    add_room_tell("Some deer watch you from a distance.");
    add_room_tell("A rabbit hops through the grass.");
    add_room_tell("A butterfly darts from flower to flower.");
    add_room_tell("The sound of a babbling brook echos nearby.");
}



public void
enter_inv(object ob, object from)
{
    if (sizeof(query_room_tells()))
	start_room_tells();
    ::enter_inv(ob,from);
}