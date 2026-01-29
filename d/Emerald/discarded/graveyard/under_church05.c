#include "/d/Emerald/common/guild/vamp/guild.h"

inherit VAMP_ROOM_DIR + "vamp_room";

#include "defs.h"

#define OTHER_ROOM (GRAVEYARD_DIR + "sun_chamber")

void
create_vamp_room()
{
    object door;

    set_short("Narrow hallway");
    set_long("   A cramped hallway leading a short distance north " +
        "from the main passage.  A square recess is set into the wall " +
        "on the west side.\n");

    add_item(({ "passage", "main passage" }),
        "This hallway leads out to the main passage to the south.\n");

    add_item(({ "recess", "square recess", "west wall" }),
        "There is a recessed block in the western wall near the door.  " +
       "It seems slightly loose.\n");

    add_exit("under_church03", "south");

    setuid();
    seteuid(getuid());

    door = clone_object(GRAVEYARD_DIR + "obj/door");
    door->set_other_room(GRAVEYARD_DIR + "sun_chamber");
    door->set_pass_command(({ "west", "w", "enter" }));
    door->move(this_object(), 1);
}

int
push_block(string str)
{
    if (!strlen(str))
    {
        return 0;
    }

    if (!parse_command(str, ({}), "[the] [recessed] 'block' / 'recess'"))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    write("You push the block.\n");
    say(QCTNAME(this_player()) + " pushes the recessed block in the wall.\n");

    setuid();
    seteuid(getuid());
    OTHER_ROOM->start_open();

    return 1;
}

int
fail(string str)
{
    if (!strlen(str))
    {
        return 0;
    }

    if (!parse_command(str, ({}), "[the] [recessed] 'block' / 'recess'"))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    write("You can't get a grip on the block.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(fail, "pull");
    add_action(push_block, "push");
    add_action(push_block, "press");
}
