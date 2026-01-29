/*
 *  /d/Gondor/guilds/rangers/hq/ucorridor2.c
 *
 *  A room upstairs in the Central Headquarters hideout
 *
 *  Coded by Alto, 21 June 2001
 *    Original theme of Druedain hideout by Elessar
 *
 */
inherit "/d/Gondor/std/room.c";

#include "../rangers.h"

inherit RANGERS_HQ_DIR + "ch_funcs.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

public int         exit_hideout();
public string      long_desc();


string
long_desc()
{
    if (Tstand->query_torch_is_lit())
    {
        return "In this second-floor corridor of the "
            + "hideout, the walls to the east and west are so close that "
            + "you can touch them both from the center of the hallway. "
            + "The wooden floor creaks beneath your feet, "
            + "not as a result of poor carpentry, but rather because the "
            + "hideout stands partially in the trees and was built by clever "
            + "hands to shift in the wind. Looking to the north, you see a "
            + "set of wooden stairs, while to the south there appears to be "
            + "bulletin board. "
            + "The room is lit by an iron torch stand mounted on the west "
            + "wall, although some light enters through a small window set "
            + "into the east wall.\n";
    }

    return "In this second-floor corridor of the "
        + "hideout, the walls to the east and west are so close that "
        + "you can touch them both from the center of the hallway. "
        + "The wooden floor creaks beneath your feet, "
        + "not as a result of poor carpentry, but rather because the hideout "
        + "stands partially in the trees and was built by clever hands "
        + "to shift in the wind. Looking to the north, you see a set of "
        + "wooden stairs, while to the south there appears to be "
        + "bulletin board. "
        + "The room is lit only by the dim light entering through a small "
        + "window set into the east wall.\n";    
}

void
create_gondor()
{
    set_short("a narrow corridor on the second floor");
    set_long(&long_desc());

    add_exit(RANGERS_HQ_DIR + "uphall", "north", 0, 1);
    add_exit(RANGERS_HQ_DIR + "office", "south", 0, 1);

    hideout_add_items();

    add_item(({"corridor", "hallway"}), &long_desc());
    add_item(({"window", "small window"}), "The small window looks just "
        + "large enough to slip through.\n");
    add_item(({"wall", "walls"}), "There are two walls here, one to the "
        + "east and one to the west.\n");
    add_item(({"west wall", "wall to the west"}), "The west wall, like most "
        + "things in the "
        + "hideout, is constructed from wood. You feel a warm glow in this "
        + "place, rather unlike the cold stone rooms and dwellings in "
        + "so-called civilized regions. This wall is also a little warmer "
        + "as a result of the iron torch stand mounted upon it.\n");
    add_item(({"east wall", "wall to the east"}), "The east wall, like most "
        + "things in the "
        + "hideout, is constructed from wood. You feel a warm glow in this "
        + "place, rather unlike the cold stone rooms and dwellings in "
        + "so-called civilized regions. There is a small window set into "
        + "the wall.\n");
    add_item(({"apprentice", "apprentice ranger"}), "You are too late! "
        + "Ranger apprentices are usually too busy with their duties to "
        + "stand around long enough to be looked at.\n");
    add_item(({"stairs", "wooden stairs"}), "Why don't you go north and "
        + "get a better look?\n");
    add_item(({"bulletin board", "board"}), "Why don't you go south and "
        + "get a better look?\n");

    add_cmd_item(({"window", "through window", "small window", 
        "through small window"}), "slip", &exit_hideout());

    add_prop(ROOM_I_INSIDE, 1);
    set_alarm(1.1, 0.0, &add_prop(ROOM_I_LIGHT, &daylight()));

    reset_room();
}

void
reset_room()
{
    set_alarm(1.0, 0.0, &hideout_add_torch());
}

int
exit_hideout()
{
    write("You slip quietly through the small window.\n");
    say(QCTNAME(TP) + " slips quietly through the small window.\n");
    tell_room(RANGERS_HQ_DIR + "vantage1", QCTNAME(TP) + " slips quietly "
        + "in through the small window.\n");

    TP->move_living("M", RANGERS_HQ_DIR + "vantage1", 1, 0);

    return 1;
}

