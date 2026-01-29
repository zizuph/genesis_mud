/*
 * Tell room for Forgotton Inn along the Eastroad.
 * - Jaypeg 30th Jan 1999 -
 */

#include <macros.h>
#include <stdproperties.h>

inherit "/d/Shire/std/room/room_tell";
//EAST_ROAD;

void create_room();
{
    set_tell_time(25);
    add_tell("A sudden chorus of wolves howling rings out close by.\n");
    add_tell("You think you see the glow of golden eyes watching you "+
             "at the edge of your vision.\n");
    add_tell("A clinging plume of sea-spray drifts up and over you.\n");
    add_tell("You hear a high-pitched squeal and scuffling that you "+
             "immediately associate with rats.\n");
    add_tell("A soft rhythm of leathery wings flapping alerts you "+
             "to a pack of bats flying overhead.\n");
    add_tell("The earth below you vibrates subtly as an unusually "+
             "large breaker hits the cliffs.\n");
    add_tell("Heavy, black clouds rush by, swept on by the angry "+
             "sea winds.\n");
    add_tell("You shudder as you have a sense of being watched.\n");
    add_tell("Shadows shift at the edge of your vision. Turning, "+
             "however, you can make out nothing unusual.\n");
    add_tell("The wind in the chasm howls briefly, like the despair "+
             "of a million tortured souls.\n");
    create_ov_road();

}

enter_inv(object ob, object from)
{
    start_room_tells();
    ::enter_inv(ob, from);
}


leave_inv(object ob,object to)
{
    stop_room_tells();
    ::leave_inv(ob, to);
}

void
create_ov_road()
{
   // fill this in in the room which inherits this file
}
