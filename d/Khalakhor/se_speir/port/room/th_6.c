/*
 * th_6.c
 *
 * This is the Lord's office for the town hall of port macdunn.
 *
 * Khail - June 4/97
 */
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "room.h"
#include "/d/Khalakhor/sys/defs.h"

inherit "/d/Khalakhor/std/room";

object lord;

public int *
query_local_coords()
{
    return ({9,4});
}

public int *
query_global_coords()
{
    return VILLAGE_COORDS;
}

public void
reset_room()
{
    if (!lord)
    {
        reset_euid();
        lord = clone_object(NPC + "fahlmar");
        lord->arm_me();
        lord->move(TO);
        tell_room(TO, QCTNAME(lord) + " straightens up from " +
            "behind his desk.\n");
    }
    else if (!present(lord, TO))
    {
        if (lord->query_attack())
            return;
        lord->command("emote looks around and realizes he " +
            "should be in his office.");
        lord->move(TO);
        lord->command("emote arrives from the reception " +
            "room.");
        lord->command("emote apologizes for his absense.");
    }
}

public void
create_khalakhor_room()
{
    set_short("Lord's office");
    set_long("   You've entered the office of Fahlmar Macdunn, " +
        "Thane of the Clan Macdunn and Lord of Port Macdunn. " +
        "The office is moderately furnished, with a desk " +
        "and chair for Fahlmar himself, and a few seats " +
        "for guests. A large claymore hangs behind the " +
        "desk on the wall, flanked on either side by large " +
        "lochaber axes, and topped off by a targe bearing " +
        "the Macdunn coat of arms.\n");

    add_item(({"walls"}),
        "The walls of the building a covered in well crafted "+
        "wooden panels.\n");
    add_item(({"panels", "wooden panels"}),
        "The panels are the product of a master carpenter, "+
        "quite possibly made from oak.\n");
    add_item(({"walkway"}),
        "You can't see much of it from here, but " +
        "it leads out into the street.\n");
    add_item(({"ground", "floor"}),
        "The floor of the room has been constructed from " +
        "tightly-jointed planks.\n");
    add_item(({"planks"}),
        "Judging from the amount of wear, this room " +
        "receives both a lot of visitors, as well as " +
        "upkeep to maintain the strength of the flooring.\n");
    add_item(({"ceiling"}),
        "The ceiling is lightly arched, and covered in " +
        "the same panels which adorn the walls.\n");
    add_item(({"desk"}),
        "The desk is covered in tidy piles of papers, " +
        "and appears to be made of oak.\n");
    add_item(({"chair"}),
        "The chair behind the desk is made of oak, and " +
        "carefully carved to resemble a small throne.\n");
    add_item(({"seats"}),
        "A few small seats, little more than stools, " +
        "really, stand against a wall for visitors to " +
        "sit on. They look incredibly uncomfortable, " +
        "however, Fahlmar doesn't seem to appreciate " +
        "long visits.\n");
    add_item(({"claymore"}),
        "The claymore is a truely massive sword, not " +
        "one that could be wielded by the average man.\n");
    add_item(({"axes", "axe"}),
        "The lochaber axes are identical, with brutal " +
        "axe heads on the ends of long shafts, and beak-" +
        "like hooks on the back.\n");
    add_item(({"targe"}),
        "The targe is a heavy wooden shield common to " +
        "the warriors of Khalakhor, though it's rare " +
        "to see one with a clan's coat of arms on it, " +
        "they are frequently the prized possessions of " +
        "the Thane of a clan.\n");

    INSIDE;

    add_exit(ROOM + "th_3", "west");
    reset_room();
}
