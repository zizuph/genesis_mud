/*
 * coded by Amelia 7/26/97
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/std/room";
inherit "/d/Earthsea/lib/room_tell";
inherit "/d/Earthsea/gont/tenalders/high_fall/climb";

public void
create_earthsea_room()
{
    set_short("Limestone cliff");
    set_long("You are climbing the side of a " +
        "tall cliff that extends up into a cloud of mist. " +
        "You must use your hands and feet to climb, as " +
        "there is precious little purchase for you to " +
        "hold onto. The mist swirls around you, blocking " +
        "your view of the surrounding area.\n");
    set_next_up("/d/Earthsea/gont/tenalders/high_fall/cliff_top");
    set_next_down("/d/Earthsea/gont/tenalders/high_fall/cliff4");
    add_tell("The roaring sound of water hurts your ears.\n");
    add_tell("You are surrounded by a cloud of mist.\n");
    add_tell("Mist gets into your eyes, making it difficult to " +
        "see where to put your hands and feet.\n");
    reset_room();
    set_tell_time(30);
}

public void
init()
{
    ::init();
    add_action(climb_cliff, "climb");
}
