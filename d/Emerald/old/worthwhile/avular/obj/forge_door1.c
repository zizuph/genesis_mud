#include "../defs.h"
#include <macros.h>
#include <language.h>

inherit "/d/Emerald/std/door";

create_emerald_door()
{
    set_name("door");
    set_adj( ({"curved", "black", "iron" }) );
    set_long("A small, curved, black-iron door rests deep within the sloped "+
        "stone wall of the building.\n");
    set_open(0);
}

public void
door_open_hook()
{
    write("You push open the small, heavy door.\n");
    say(QCTNAME(TP)+" pushes open the small, heavy door.\n");
    tell_room(query_other_room(), LANG_THESHORT(other_door) + " slowly opens "+
              "with a grinding noise.\n");
}

public void
door_close_hook()
{
    write("You slide the door closed with a grinding noise. Despite its low "+
        "height, it is an extremely heavy door.\n");
    say(QCTNAME(TP)+" slides the door closed with a grinding noise.\n");
    tell_room(query_other_room(), LANG_THESHORT(other_door) + " slides closed "+
        "with a grinding noise.\n");
}

public void
door_knock_hook()
{
    write("You knock on the door, noting that you don't make much of a "+
        "noise, banging on dense, solid iron.\n");
    say(QCTNAME(TP)+" knocks on the door, barely making a noise against "+
        "the dense, solid iron.\n");
    tell_room(query_other_room(), "A very faint knocking can be heard on "+
        "the other side of " + LANG_THESHORT(other_door) + ".\n");
}

public int
prevent_lock_door()
{
    write("You can't find any lock or keyhole on the door with which to "+
        "lock it.\n");
    return 1;
}

public int
prevent_unlock_door()
{
    write("The door is not currently locked, and has no keyhole in order "+
        "to be locked.\n");
    return 1;
}

