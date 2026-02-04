/*
 * cave_room.c
 *
 * A generic orc cave room.  All the orc caves rooms should inherit this
 * file.
 *
 * Modified by Lilith Aug 12, 2008
 * -Updated the enable_reset() to 115mins
 *
 * Lucius - Jan 2021
 *   Cleaned up and modernized.
 */
#include "/d/Terel/include/Terel.h"

inherit STDROOM;
inherit "/d/Terel/std/room_tell";

/*
 * Function name: init
 * Description:   Add the 'command items' of this object.
 */
public void
init(void)
{
    ::init();
    start_room_tells();
}

/*
 * Function name: hook_smelled
 * Arguments:     string str - An add-item
 * Description:   What does the air smell like here?
 * Returns:       The description of the smell
 */
public void
hook_smelled(string str)
{
    if (!strlen(str))
        write("There is a smell of foul creatures in the air.\n");
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_terel_room()
{
    set_short("cave");
    set_long("You are in a large complex of tunnels and caves. " +
             "Stalactites hang down from above and stalagmites protrude " +
             "from the ground. The walls are somewhat damp with moisture. " +
             "The air is cool and carries a strange scent. ");

    add_item(({"stalagmites", "stalagmite"}),
             "They vary in size and are a bit lighter in colour than the " +
             "ground from which they come.\n");

    add_item(({"stalactites", "stalactite"}),
             "Hanging down from the ceiling, they have a rough texture. " +
             "Some of them drip water onto the cavern floor.\n");

    add_item(({"wall", "walls","rocks","rock"}),
             "The walls have the same rough texture as " +
             "the stalagmites, but are darker in colour. Lower down dried " +
             "leaves and twigs are stuck on, indicating the water " +
             "level must have been higher in here recently.\n");

    set_tell_time(100 + random(200));
    add_tell("A drop of water drips from the stalactites above you.\n");
    add_tell("You hear the sounds of small wings beating in the distance.\n");

    INSIDE;

    /* ~115 minutes between reset instead of 90 */
    enable_reset(75);
}
