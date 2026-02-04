/*
   This is a small room in the witch cottage. Mortricia 920721
   Modified to include a kiss function. Mortricia 920723
 */
inherit "/std/room.c";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

#define HOME_DIR "/d/Terel/silver/cottage/"
#define BS(message)       break_string(message, 70)
#define TP                this_player()
#define TO                this_object()
#define HARD_TO_KISS      25

reset_room()
{
    object toad;

    if (present("toad") || present("azure"))
        return;
    toad = clone_object(HOME_DIR + "toad");
    toad -> move(TO);
}

init()
{
    add_action("kiss", "kiss");
    ::init();
}

create_room()
{
    object door;

    set_short("Cottage room");
    set_long(BS(
        "You are inside a small storage room in the northern part of " +
        "the cottage. The floor is very slimy.\n"));

    add_item(({"wall", "walls"}), "The walls are all black.\n");
    add_item(({"slime"}), "Something must be real slimy in here!\n");

    add_prop(ROOM_I_INSIDE, 1);

    door = clone_object(HOME_DIR + "black_door2");
    door -> move(TO);

    reset_room();
}

kiss(string str)
{
    object toad;

    toad = present("toad");
    if (str != "toad" || !toad)
    {
        return 0;
    }

    if (toad -> query_name() == "corpse")
    {
        write(BS("You do not have the guts to kiss the dead toad.\n"));
        say(BS(QCTNAME(TP) + " tried to kiss the dead toad. " +
            "It's disgusting.\n"));
        return 1;
    }

    if (TP -> query_skill(SS_ANI_HANDL) < 10 + random(HARD_TO_KISS))
    {
        write(BS("You didn't have the guts to do that. " +
                 "The toad is too slimy.\n"));
        say(QCTNAME(TP) + " tried to kiss the toad but failed.\n");
        return 1;
    }

    toad -> remove_object();

    write(BS("POOF! When you kiss the toad it disappears into a dark cloud " +
             "of smoke. As the smoke disperses the contours of a human " +
             "become discernible.\n"));
    say(QCTNAME(TP) + " managed to kiss the slimy toad.\n");

    clone_object(HOME_DIR + "prince") -> move(TO);

    return 1;
}
