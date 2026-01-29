/* /d/Gondor/lebennin/wolfcave/ranger_caves/rcave10.c
 *
 * Coded by Tigerlily, 2004-10-16
 * Caves where white_warg lives--last task for
 * Ranger apprentices is to kill the warg in team with
 * exactly one company ranger 
 * Some descriptions borrowed from the wolfcave.
 */

inherit "/std/room.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/rangers/rangers.h"
#include "cave_defs.h"

object warg;

int access_cave();

void
reset_room()
{
    if (!objectp(warg))
    {
        warg = clone_object(RANGERS_NPC + "white_warg");
        warg->move(TO, 1);
        warg->command("emote comes bounding in with a roar!");
        return;
    }
}

public void
create_room()
{
    set_short("lair of the beast");
    set_long("This is the lair of the beast. Debris is " +
        "scattered around the rocky floor, and the " +
        "walls are covered with some kind of fungus. An odd " +
        "smell permeates the air.\n");
    add_item(({"debris"}), "Debris consisting of dirt, dead leaves, " +
        "bones, rocks, twigs, and partially rotted carcasses of " +
        "various animals lie around on the floor.\n"); 
    add_item(({"rocks","twigs", "marks"}), 
        "Not very interesting, just normal rocks and twigs with " +
        "tiny scratch marks.\n");
    add_item(({"ceiling"}), "The ceiling is composed of time worn rock.\n");
    add_item(({"floor"}), "The floor is composed of time worn rock.\n");
    add_item("fungus", "Some sort of fungus grows on the walls here " +
        "feeding on the damp environment.\n");
    add_item(({"walls","wall"}), "Composed of time worn rock, the walls are " +
        "pockmarked with holes. There is a particularly large hole " +
        "in the north wall, large enough for a human to enter.\n");
    add_item(({"opening", "north wall", "hole", "large hole"}),
        "The north wall contains an " +
        "opening into another cave.\n");

    add_exit(CAVE_PATH + "rcave9", "west", 0, 0, 1);
    add_exit(CAVE_PATH + "tcave", "enter", &access_cave(), 0, 1);

    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_LIGHT, -1);  
    add_prop(ROOM_I_INSIDE, 1); 
    reset_room();
}

public void
hook_smelled(string str)
{
    write("The foul stench of a wild beast mixed with the smell " +
        "of rotting carcasses assails your nostrils. Your nose tells " +
        "you that this is the lair of some evil beast.\n");
    return;
}

int
access_cave()
{
    if (present(warg, TO))
    {
        write("The warg prevents you from entering the hole!\n");
        warg->command("emote growls fiercely and slams you with " +
            "his massive paw!");
        return 1;
    }
    return 0;
}

