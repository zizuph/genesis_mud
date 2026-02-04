/*
    A test room
 */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

#define BS(message)    break_string(message, 70)
#define TP             this_player()
#define TO             this_object()
#define HARD_TO_KISS   25

object toad;

void
reset_room()
{
    if (!present("pot")) {
        clone_object("/d/Terel/mortricia/objects/pot") -> move(TO);
    }
    if (!present("powder")) {
        clone_object("/d/Terel/mortricia/objects/powder") -> move(TO);
    }
    if (!present("snow")) {
        clone_object("/d/Terel/mortricia/objects/snow") -> move(TO);
    }
    if (present("toad") || present("azure"))
        return;
    toad = clone_object("/d/Terel/mortricia/creatures/toad");
    toad -> move(TO);
}

init()
{
add_action("kiss", "kiss");
add_action("test", "test");
::init();
}

void
create_room()
{
    set_short("Basic room");
    set_long(BS("It's a very basic room as you can see.\n"));

    add_prop(ROOM_I_INSIDE, 1);

    add_item("slime", BS("It's very slimy slime.\n"));

    reset_room();
}

kiss(string str)
{
    if (str != "toad" || !present("toad"))
    {
        return 0;
    }

    if (TP -> query_skill(SS_ANI_HANDL) < 5 + random(HARD_TO_KISS))
    {
        write(BS("You didn't have the guts to do that. " +
                 "The toad is too slimy.\n"));
        say(QCTNAME(TP) + " tried to kiss the toad but failed.\n");
        return 1;
    }

    toad -> remove_object();

    write(BS("POOF! The toad disappears into a dark cloud of smoke." +
        " When the smoke disperses the contours of a human becomes " +
        "visible.\n"));

    clone_object("/d/Terel/mortricia/people/prince") -> move(TO);

    return 1;
}

test(string str)
{
    object *stuff;
    int i;

    stuff = all_inventory(this_player());

    for(i=0; i<sizeof(stuff); i++) {
        if (!interactive(stuff[i])) {
            if ( (stuff[i])->query_name() == str )
                {
                write("It's here!\n");
                return 1;
            }
        }
    }
    write("Not found!\n");
    return 1;
}
