/* Basic room, ready-made for modification, Azireon. */
/* Modified by Azireon, September 11, 1992, concert_hall.c */

inherit "/std/room";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Terel/common/terel_defs.h"

object soprano;
int x;

reset_room(arg)
{
    if (x == 1)
    {
        soprano->remove_object();
        x = 0;
    }
    else
    return 1;
}

create_room()
{
    set_short("Concert Hall Stage");
    set_long(break_string(
        "The size of this chamber is incredible.  Its floor is " +
        "contoured in such a way that it slopes into the center " +
        "where the large ovalur marble stage that you stand on " +
        "has been raised.  Water " +
        "seeps and drips from the ceiling and walls and a pool has " +
        "formed around the stage.  The smell of mildew is unbearable." +
        "  A large box or case stands on three legs in the center " +
        "of the stage;  several dirty blankets have been draped " +
        "over it.  There is a vast circular opening in the vaulted " +
        "ceiling.\n", 70) );

    add_item( ({ "opening", "ceiling" }),
        break_string(
        "Far above, you can make out strange bas-relief work that " +
        "covers the ceiling with a maze of images.  From here you " +
        "can gaze far up into a massive gilded dome that leaves " +
        "you with a dizzying sense of space.  There are frescoes " +
        "but, from this distance, they are impossible to see " +
        "clearly.  You think you can make out a human figure " +
        "standing at a railing but you cannot be sure.\n", 70) );

    add_item( ({ "water", "pool" }),
        break_string(
        "The pool is quite rancid;  the water and humidity have " +
        "rotted anything of value in the chamber.\n", 70) );

    add_item( ({ "box", "case" }),
        break_string(
        "Upon closer examination, you realize that this is what " +
        "used to be a small harpsichord.  It has been covered " +
        "with filthy wool blankets that drape down, creating a " +
        "small shelter beneath the instrument.  A revolting smell " +
        "and a deranged whispering sound emanate from within.\n", 70));

    add_cmd_item( "harpsichord", "play", "@@play" );
    add_cmd_item( ({ "blanket", "blankets" }),
        ({ "move", "open" }),
        ({ "@@lunatic", "@@lunatic" }) );

    add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room. */
    add_prop(ROOM_HAS_WATER, 1);  /* For Dust's quest! */

    add_exit(MANSION + "second/concert_hall", "south", 0);

    reset_room();
}

play()
{
    write("Touching the rotted keys, you try to play the harpsichord.\n");
    write("No matter what your musical ability, you fail miserably.\n");
            /* This may be changed if minstrel guild is implemented. */
    write("It has been damaged irreparably.\n");
    say(QCNAME(this_player()) + " makes an awful sound on the harpsichord.\n");
    say("You wish they would stop.\n");
    return 1;
}

lunatic()
{
    seteuid(getuid());  /* Won't clone in VBFC otherwise... */

    write("You draw aside the blankets on the harpsichord.\n");
    say(break_string(QCNAME(this_player()) +
        " draws aside the blankets on the harpsichord.\n", 70) );


    /* She should only come out if she is not already in the room;
     * however, if she has been killed, she should not come out
     * again until th room resets.
     */
    if (x == 0)
    {
    write("A strange woman comes bounding out from underneath it.\n");
    say("A strange woman comes bounding out from underneath it.\n");
    soprano=clone_object(MANSION + "second/soprano");
    soprano->move(this_object());
    x = 1;
    return 1;
    }
    else
    return 1;
}
