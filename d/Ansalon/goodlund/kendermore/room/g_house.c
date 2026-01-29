/* House of a gnome in Kendermore, Gwyneth, June 1999 */

#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>

inherit STREET_DESC;
inherit KENDERMORE_IN;

object kinanserofin;
int found_stuff = 0;

void
reset_kendermore_room()
{
    if (!kinanserofin)
    {
        kinanserofin = clone_object(KNPC + "kinan");
        kinanserofin->move(TO);
    }
    found_stuff = 0;
}

void
create_kendermore_room()
{
    set_short("A crowded gnomish house");
    set_long("This house is crowded from floor to ceiling with gizmos, " +
        "gears, and other hard to identify pieces of metal. A crowded table " + 
        "sits in one corner with a hard wooden chair pushed up against it. " + 
        "There isn't much else to decorate the place except for the many " + 
        "shelves that line the walls and a simple bed near the table. " + 
        "There's a front door to the west, and a back door to the east. A " + 
        "window has been set in the west wall near the door.\n"); 
    add_item("table", "It's crowded with complicated gizmos.\n");
    add_item("chair", "It looks a bit uncomfortable.\n");
    add_item(({"gizmos", "gadgets"}), "Who knows what they do.\n");
    add_item(({"jars", "pots", "trowels", "books"}), "They all seem to be " + 
        "related to gardening and herbs.\n");
    add_item(({"street", "window"}), "@@street_descr@@\n");
    add_item(({"shelf", "shelves", "wall","walls"}), "The shelves are " + 
        "secured to the wall, and very crowded with gizmos, gadgets, jars, " + 
        "pots, trowels, and books.\n");
    add_item(({"bed", "simple bed"}), "The covers are thrown at the foot of " +
        "the bed. The occupant doesn't seem to be a very tidy person.\n"); 
    add_item("door", "Which door?\n");
    add_item("front door", "It leads out into the streets of Kendermore.\n");
    add_item("back door", "It looks very solid.\n");
    add_exit(KROOM + "street38", "west", "@@front_door");
    add_exit(KROOM + "gnome12", "east", "@@back_door");

    set_tell_time(300);
    add_tell("You hear a shrill voice yelling: Gotcha!\n");
    add_tell("Bright laughter rings out from the street.\n");
    add_tell("You hear the sound of glass shattering next door.\n");
    add_tell("A gizmo falls from a shelf with a loud crash.\n");

    reset_kendermore_room();
    return;
}

int
back_door()
{
    write("You open the back door and step outside.\n");
    say(QCTNAME(TP) + " opens the back door and steps outside.\n");
    return 0;
}

int
front_door()
{
    write("You open the front door and step into the street.\n");
    say(QCTNAME(TP) + " opens the front door and steps into the street.\n");
    return 0;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}
