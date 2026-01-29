/* This is a room in the elemental area northeast of the
frog pond in Calia. By Bishop, 5.2.99 */

inherit "/std/room";

#include <stdproperties.h>
#include <ss_types.h>
#include <pond.h>
#include <macros.h>

create_room()
{
    set_short("In a dim corridor");

    set_long("It's fairly dark in the west end of the corridor," +
        " but it is" +
        " brightened by light coming from up ahead. To the west" +
        " you can vaguely see a dark pool and to your east you" +
        " see a red glow. You feel heat coming from the same" +
        " direction as the glow.\n");

    add_item(({"corridor", "walls"}), "The walls of the corridor" +
        " itself are very smooth.\n");
    add_item("light", "You can't get a good look at the source of" +
        " the faintly red light.\n");
    add_item(({"dark pool", "pool"}), "You can barely see the pool" +
        " from here.\n");
    add_item("glow", "A reddish glow originates in the east" +
        " somewhere and casts the walls in a faint red light.\n");

    add_prop(ROOM_I_HIDE, 20);
    add_prop(ROOM_I_INSIDE, 1);

    add_exit(FPATH + "env_und_pool", "west", 0, 1);
    add_exit(FPATH + "hot_room", "east", 0, 1);
}