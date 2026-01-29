/*
 * /d/Gondor/guilds/militia/room/start.c
 *
 * This code is copyright (c) 2001 by Scott A. Hardy and Alyssa Hardy.
 * Genesis is a game currently run through Chalmers University.
 * Scott and Alyssa Hardy have seen the 1991 document of Genesis'
 * called 'legal', and they do not forfeit any of their intellectual
 * property rights as that document supposes they would.  They are the
 * sole and complete owners of this code, which as of April 2001 they are
 * loaning to Genesis.  Genesis does not own this code, or
 * have any right to transfer it to anyone.  By its ongoing
 * use and storage of their code, Genesis acknowledges and agrees
 * to all of the above.
 *
 * The start room for the militia.
 * 
 * Coded by Auberon and Gwyneth on 19 February 2001
 */
inherit "/d/Gondor/std/room";

#include "../militia.h"
#include <macros.h>
#include <stdproperties.h>

// object gRack1, gRack2;

void
reset_gondor_room()
{
/*
    if (!present(gRack1))
    {
        gRack1 = clone_object(MOBJ + "eq_rack");
        gRack1->move(this_object(), 1);
    }
*/
/*
    if (!present(gRack2))
    {
        gRack2 = clone_object(MOBJ + "neq_rack");
        gRack2->move(this_object(), 1);
    }
*/
}

public void
create_gondor()
{
    set_short("The Militia bunkroom");
    set_long("This room is rather plain. Most militia sleep in their own " +
        "houses, so the accomodations are not exactly luxurious, merely " +
        "functional. Of course, any member of the militia is welcome to " +
        "'sleep' here. There are a few bunk beds lining the bare walls, " +
        "a straw-covered floor, and a couple of wooden equipment racks.\n");
    add_item(({"bed", "beds", "bunk beds"}), "The bunk beds are all very " +
        "neatly made with neatly woven blankets made by the women of " +
        "Thornlin.\n");
    add_item(({"blankets", "woven blankets", "neatly woven blankets",
        "blanket"}), "They are made of wool and coloured with natural " +
        "earthy dyes. On a cold winter night, any one of the blankets " +
        "would be very welcome.\n"); 
    add_item(({"straw", "floor", "straw-covered floor"}), "The straw on the " +
        "floor is fresh and clean, and has a few herbs mixed in to repel " +
        "fleas.\n");
    add_item(({"wall", "walls", "bare walls", "ceiling", "brick"}),
        "The walls and ceiling are made of good quality brick, and the " +
        "workmanship appears to be that of local mason who took great " +
        "pride in his work and making the buildings of his town look nice.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_M_NO_ATTACK, 1);
    add_prop(ROOM_M_NO_MAGIC_ATTACK, 1); 
    add_exit(MROOM + "join.c", "south", 0, 1, 0);   
    reset_gondor_room();

    room_add_object(MOBJ + "rack");
}

private int
start(string str)
{
    if (!IS_MILITIA(this_player()))
    {
        notify_fail("Only members of the militia may sleep here.\n");
        return 0;
    }
    else if (this_player()->set_default_start_location(MSTART))
    {
        write("You decide to sleep here, and here you will awaken.\n");
        return 1;
    }
    else
    {
        notify_fail("Some problem prevents you from starting here.\n" +
            "Please make a bug report.\n");
        return 0;
    }
}

void
remove_militia_members(object who)
{
    who->catch_tell("A stern looking guard escorts you out of the " +
        "barracks.\n");
    tell_room(this_object(), QCTNAME(who) + " is escorted out of the " +
        "barracks by a stern looking guard.\n", who);
    tell_room(THORN_DIR + "r2a", QCTNAME(who) + " is escorted out from " +
        "the barracks by a stern looking guard.\n");
    who->move_living("M", THORN_DIR + "r2a", 1, 0);
}

int
did_spit(string str)
{
    remove_militia_members(this_player());
    return 1;
}

public void
init()
{
    ::init();

    add_action(did_spit, "spit");
    add_action(start, "start");
    add_action(start, "sleep");
}
