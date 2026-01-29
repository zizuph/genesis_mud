/*
 *  /d/Gondor/guilds/rangers/ithilien/passage1.c
 *
 * Modification log:
 *  3-Dec-1996, Olorin: Typo fix, some cosmetic changes.
 *  20-Jul-2001,Alto: more tidy up, change inheritance for new
 *                    rangers.
 *  26-March-2004-Tigerlily: added secret exit
 */
inherit "/d/Gondor/std/room.c";

#include "../rangers.h"

inherit RANGERS_ITH_DIR + "ith_funcs.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "exit.c"

public void    reset_room();
object  gRanger;
int enter_tunnel(string str);

public void
create_gondor()
{
    set_short("a dark winding passage");
    set_long("You are in a dark and narrow passage, with walls rough "
        + "and uneven. The passage turns around a corner here, leading "
        + "north and east. You hear the sound of water to the north, "
        + "rushing and splashing. A flight of wet steps leads up from "
        + "here.\n");
    add_exit(RANGERS_ITH_DIR + "window", "north", &check_ranger(0, gRanger));
    add_exit(RANGERS_ITH_DIR + "passage2", "east", &check_ranger(0, gRanger));
    add_exit(RANGERS_ITH_DIR + "post", "up", &check_ranger(0, gRanger), 2);
    add_item("walls", "They are rough and unevenly cut. You notice " +
         "something unusual about the blocks on the west wall.\n");
    add_item(({"west wall", "block", "blocks", "wall"}), "Your keen eyes " +
        "notice what appears to be the outline of a door set into " +
        "the west wall.\n");
    add_item(({"door", "outline of a door", "outline"}), "Push the " +
        "door and see what happens.\n");
    add_item("passage", "The passage continues in darkness east, but "
        + "you see a little light to the north.\n");
    add_item("steps", "A steep flight of steps lead up from here. Water "
        + "glistens on the roughly cut stone of each step.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_M_NO_SCRY, 1);

    reset_room();
}

public void
reset_room()
{
    if (!objectp(gRanger))
        gRanger = clone_npc(gRanger, (RANGERS_NPC + "ith_ranger"));
}

void
init()
{
    ::init();
    add_action(&enter_tunnel(), "push");
}

int
enter_tunnel(string str)
{
    object tp = this_player();

    if (!CAN_SEE_IN_ROOM(tp))
    {
        notify_fail("You cannot see anything " +
            "to push here.\n");
        return 0;
    }

    if (!RANGERS_MEMBER(tp))
    {
        notify_fail("You push against the wall " +
            "and work up a sweat, but nothing " +
            "happens.\n");
        return 0;
    }

    if (str != "door" && str != "wall")
    {
        notify_fail("Push door?\n");
        return 0;
    }
    write("You push hard against the wall, and suddenly it " +
        "opens.\nYou fall into a secret passageway.\n");
    tell_room(environment(tp), QCTNAME(tp) + " pushes " +
        "against the wall and it suddenly swings open.\n", ({tp}));
    
    tp->move_living("through the wall", 
        RANGERS_ITH_TUNNEL + "tunnel01", 1, 0);
    return 1;
}

    

