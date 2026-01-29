/* Dark alley in Kendermore, Gwyneth, June 1999 */

#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>

inherit STREET_DESC;
inherit KENDERMORE_OUT;

object merc;

void
reset_kendermore_room()
{
    if (!merc)
    {
        merc = clone_object(KNPC + "jane");
        merc->move(TO);
    }
}

void
create_kendermore_room()
{
    set_short("A dimly lit alley");
    set_long("@@long_descr");
    add_item("shadows", "Anything could be hiding in them.\n");
    add_item(({"house", "houses", "buildings"}), "Even the houses here have " +
        "a carefree feeling. " +
        "There doesn't seem to be any way in from here.\n");

    add_exit(KROOM + "street26", "south", 0);

    set_tell_time(100);
    add_tell("A kender bumps into you, apologizes and continues on " + 
        "his way.\n");
    add_tell("Bright laughter rings out from nearby.\n");
    add_tell("A kender arrives, excitedly picks up a piece of shiny " + 
        "metal from the ground, and happily skips away.\n");
    add_tell("A small mouse scurries across your path.\n");
    add_tell("A loud crashing sound reaches your ears.\n");
    add_tell("A small bug skitters under a bush.\n");
 

    reset_kendermore_room();
    return;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}

string
long_descr()
{
    return (tod_descr() + season_descr() + "Houses stand on both sides " + 
        "of you. " + street_descr() + " This is a small spot between two " + 
        "buildings. The light is dim, and the shadows lengthy.\n"); 
}

