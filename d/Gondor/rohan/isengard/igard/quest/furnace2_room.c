/*
 *  IGARD_QUEST + "furnace2_room.c"
 *
 *  Furnace room for Isengard Quest.
 *
 *  Last modified by Alto, 6 December 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../igard_defs.h"

inherit IGARD_LIB + "igard_funcs.c";
inherit IGARD_LIB + "furnace_funcs.c";

public void        create_gondor();
public int         prevent_up();
public void        move_quester_alive();

object             actor;


string
long_desc()
{
    return "Is it really HOT in here! You are standing in a large "
    + "underground room with stone walls, ceiling and floor. Most of "
    + "the room is filled with the complex components of a massive "
    + "furnace. From the grinding and clanking sounds booming from "
    + "within, you conclude that the great furnace is not working "
    + "properly. A wide stairwell leads up into darkness.\n";
}


public void
create_gondor()
{
    set_short("A great furnace room beneath Isengard");
    set_long(long_desc());

    stairwell_add_items();
    underground_add_items();
    furnace_add_items();
    furnace_extraline();
    furnace_quest_adds();
    furnace_quest_commands();

    add_item(({"room", "area", "surroundings", "place", "landing"}), 
        long_desc());

    add_item(({"furnace", "massive furnace", "broken furnace"}), "This "
        + "is one of the many massive furnaces built beneath the stinking "
        + "plain of Isengard. This particular furnace burns coal and "
        + "produces steam to drive some of the diabolical machines "
        + "Saruman has designed for industry and war. It appears to be "
        + "broken.\n");
    add_item(({"components", "complex components"}), "There are many "
        + "components to the furnace, each having a unique function necessary "
        + "to its operation. The most obvious and important component "
        + "is the pressure chamber.\n");
        

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_M_NO_MAGIC, 1);
    add_prop(ROOM_M_NO_TELEPORT, 1);

    add_exit(IGARD_QUEST   + "entry2_stair", "up", &prevent_up());

    reset_room();
}


public void
reset_room()
{
}


public int
prevent_up()
{
    write("What? Leave now? The furnace would most likely explode before "
        + "you escape! Better stay and fix it .. quickly!\n");
    return 1;
}


public void
back_to_dome()
{
    TP->move_living("M", IGARD_PLAIN_PATHS + "se_dome2", 1, 0);
}

public void
move_quester_alive()
{
    actor = TP;

    set_alarm(6.0, 0.0, &write("Having repaired the furnace and collected "
        + "your next clue, you decide to leave the furnace room as soon as "
        + "possible!\n"));
    set_alarm(6.0, 0.0, &tell_room(environment(actor), QCTPNAME(actor)
            + " decides to leave before " + HIS_HER(actor) + " luck runs "
            + "out.\n", ({actor})));
    TP->remove_prop(SENT_FURNACE_IGARD2);
    set_alarm(7.0, 0.0, &back_to_dome());

}
