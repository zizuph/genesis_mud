/* Basic room, ready-made for modification, Azireon. */
/* Modified by Azireon, Sept. 6, 1992, mansion staircases. */

inherit "/std/room";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Terel/common/terel_defs.h"

create_room()
{
    set_short("Spiral staircase");
    set_long(break_string(
        "This square room is enclosed by tall marble walls.  At one " +
        "time, it must have been very elegant but no more.  Dust and " +
        "filth have darkened the walls and floor with grime.  A " +
        "large crystal chandelier still hangs from the ceiling.  An " +
        "enormous painting in a heavy frame has fallen from the " +
        "wall and lies in a heap.  A wide marble staircase descends " +
        "majestically in a slow spiral to the floor below.\n", 70) );

    add_item( "chandelier",
        break_string(
        "Most of the crystals have either fallen out or have been " +
        "knocked out of this chandelier.  Those that remain are " +
        "coated with dust so badly that they appear gray.  Spider " +
        "webs float, ghost-like, between its arms and crystals.\n", 70));

    add_item( ({ "walls", "wall", "floor", "dust", "filth", "grime" }),
        break_string(
        "The walls and floor are made of marble that must originally " +
        "have been white.  The dirt accumulated on them would take " +
        "years to clean off adequately.\n", 70) );

    add_item( "painting",
        break_string(
        "The canvas of this painting has been slashed and a portion " +
        "has been completely removed or destroyed.  Although its " +
        "colours have severely faded, you can still tell that this " +
        "painting depicts a heroic figure, astride a horse and " +
        "playing a large harp.  The figure's face and part of his " +
        "body have been torn away.\n", 70) );

    add_item( "frame",
        break_string(
        "This heavy wooden frame has been cracked in several places. " +
        "It also has been slashed by something and possibly burned " +
        "in places, judging by some black scorch marks.\n", 70) );

    add_item( ({ "staircase", "floor below" }),
        break_string(
        "At least ten feet wide, the staircase is bordered, on one " +
        "side, by the wall and, on the other, by an elegant pillared " +
        "handrail.  All you can see of the room below is the floor, " +
        "a black and white checkered tile.\n", 70) );

    add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room. */

    add_exit(MANSION + "second/antechamber", "east", 0);
}
