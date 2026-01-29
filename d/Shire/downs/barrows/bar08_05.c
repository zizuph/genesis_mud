/* End cave of a barrow
 * Based on Dondon's downs
 * -- Finwe, December 2001
 */

#include "/d/Shire/sys/defs.h"
#include "../local.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>


inherit BAR_BASE;

int alarm_id;
int handle_status,  // status of handle 0 = it's not moved, 1 = moved 
    handle_pulled,  // number of times handle moved with wights in room
    exit_status;    // exit open or closed. 0 = closed, 1 = open
/*
void handle_moved();
*/
void
create_barrow_room()
{
    set_short("A dark passage inside a barrow");
    set_long("You stand in a large, collapsed stone cavern. There " +
        "is barely enough room to stand in here, and the ceiling " +
        "looks like it's ready to fall in anytime. There is a " +
        "handle is attached to the wall.\n");

    add_item(({"piles of dirt", "piles of earth", "clods of dirt", 
            "clods of earth", "dirt", "earth"}),
        "The piles of dirt are dark and lay in various sized " +
        "piles about the room. They have a rich, loamy look to them.\n");
    add_item(({"corpses", "rotting corpses", "skeletons"}),
        "They are travellers that were lured or fell into the " +
        "barrows who knows how long ang. Little remains of them " +
        "other than some rotting flesh and bones.\n");
    add_item(({"rotting flesh"}),
        "The rotting flesh partially covers the corpses, " +
        "revealing nothing more than bones.\n");
    add_item("bones",
        "The bones are grey colored with some teeth marks, " +
        "probably from rodents that have been chewing on them. " +
        "The bones poke out from the rotting flesh.\n");
    add_item(({"handle", "lever"}),"The handle is smooth yet " +
        "shows signs of rust. It has obviously has not been used " +
        "for a long time.\n");

    add_prop(ROOM_I_LIGHT, 0);    
    reset_shire_room();

    add_exit(BAR_DIR + "bar08_04", "east","@@check_exit@@");
    add_exit(BAR_DIR + "bar08_out", "down","@@check_handle@@");

}

init() {
    ::init();
    add_action("handle", "move");
    add_action("handle", "use");
    add_action("handle", "push");
    add_action("handle", "pull");
}


void reset_shire_room()
{
    handle_status = 0;  // handle reset to closed
    handle_pulled = 0;  // handle not pulled
    exit_status = 0;    // exit closed
    make_black_wight();
}

