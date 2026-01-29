/* A handy meditation booth for our the benefit of the Grunts.    */
/* Taken mostly from the examples. Recoded 21/08/95 by Tulix III. */

inherit "/std/room";
inherit "/lib/guild_support";

#include "default.h"
#include <macros.h>
#include <stdproperties.h>
#include "../guild.h"

void
create_room()
{
    set_short("Meditation alcove");
    set_long(
        "   You have entered a peaceful little alcove, which somehow formed " +
        "naturally from the surrounding rock. You can meditate here, " +
        "to set your learning preferences. The main Grunts' guild room is " +
       "back to the south of here.\n\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_M_NO_ATTACK, "You cannot break the peace of this place.\n");
    add_exit(THIS_DIR+"main", "south", 0, 1);

    add_item(({"walls","wall"}),
        "The walls are cold, and damp to touch. It seems to be volcanic " +
        "rock that these caves are made of. Pretty hard stuff it is, too.\n");
    
    add_item(({"roof","ceiling"}),
        "What little you can see above you suggests that the roof is made " +
        "of the same rock as the walls, volcanic rock. At least you can " +
        "be fairly sure the roof won't be falling down, as volcanic rock " +
        "is pretty tough stuff.\n");

    add_item(({"floor","ground"}),
        "The floor on which you are standing seems very firm, and is made " +
        "of volcanic rock.\n");

}

public void
init()
{
    ::init();
    init_guild_support();
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    gs_leave_inv(ob, to);
}

public void
gs_hook_start_meditating()
{
    write("" +
        "You start to meditate in the alcove.\n" +
        "You fell very calm. In this calm start you can estimate your stats " +
        "<estimate>,\n" +
        "and set your learning preferences as you wish them <set>.\n" +
        "When you are satisfied, just rise once more <rise>.\n");
    say(QCTNAME(this_player())+ " enters a state of peaceful meditation.\n");
}

public void
gs_hook_rise()
{
    write("You ascend from your state of meditation back to the world.\n");
    say(QCTNAME(this_player()) + " rises from a state of meditation.\n");
}
