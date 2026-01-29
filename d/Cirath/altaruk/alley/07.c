#include "../defs.h"
inherit STD + "room.c";
#include <macros.h>

int block();
object o;

void
reset_room()
{
    if(!present(o))
    {
        o = clone_object(ALT_STD + "barrel.c");
        o->Short_d("wodden barrel");
        o->set_content(({ALT_OBJ + "torch.c",ALT_OBJ + "torch.c" }));
        o->move(this_object());
    }
    o->make_whole();
}

void
create_room()
{
    set_short("in a dark basement.");
    set_long("In a dark forgotten basement in Altaruk." +
        " New buildings has been build over the remains" +
        " of the old ones destroyed by raiding giants." +
        " A light beams from the hole you dropped in through." +
        " The room is bare except a stone lodged in the floor" +
        " beneath the hole.\n");

    add_item("stone", "The stone lodged in the floor is the same" +
        " size as the hole in the wall above you.\n");
    
    add_prop(ROOM_I_INSIDE,1);
    add_exit(ALT_STR + "25.c", "up", &block(), 1, 0);
    add_exit("08.c", "south", 0, 1, 1);

    reset_room();
}

int
block()
{
    write("As you get ready to climb up you feel the wall" +
        " clumble in your hands. It will collapse over you" +
        " if you put your weight on it. Better find another" +
        " way out.\n");
    say(QCTNAME(this_player()) + " tries to climb up but failes.\n");
    return 1;
}