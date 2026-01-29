#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include "/d/Ansalon/goodlund/kendermore/local.h"

inherit KENDERMORE_IN;

#define RDIR      "/d/Ansalon/private/entrance/room/"

void
reset_kendermore_room()
{
}

void
create_kendermore_room()
{
    set_short("A secret passageway");
    set_long("This is a secret passageway hidden in the walls of this " + 
        "castle. Torches are mounted on the walls at regular intervals, " + 
        "but it is still difficult to see well. Cobwebs hang down from " + 
        "the ceiling, and dust coats the floor. The passageway leads " + 
        "to the north, or you can leave to the east.\n");
    add_item(({"stone", "black stone", "rough stone", "rough black stone",
        "limestone"}),
        "Rough hewn blocks of limestone make up the walls, floors and " + 
        "ceiling of this passageway.\n");
    add_item(({"wall", "walls", "stone wall",
        "stone walls", "rough wall",
        "rough walls", "rough stone wall", "rough stone walls",}), "They " + 
        "are made of limestone, and look very sturdy. Torches are " + 
        "mounted on them, lighting the passageway with a dim eerie light.\n");
    add_item(({"floor", "floors"}), "They are made of roughly cut " + 
        "limestone, and covered in dust.\n");
    add_item("dust", "It hasn't been disturbed in quite some time.\n");
    add_item("cobwebs", "They hang down from the ceiling.\n");
    add_item("ceiling", "It is made of roughly cut limestone, and covered " + 
        "with cobwebs.\n"); 
    add_item(({"torch", "torches"}), "The are large tar-drenched " + 
        "torches that light the passageway.\n");
    add_item(({"eerie shadows", "shadows", "eerie shadow", "shadow"}),
        "You can't quite see into the darkest part of the shadowed " + 
        "passageway. This looks like an excellent place to sneak around.\n"); 

    add_exit(RDIR + "passage", "north", "@@end_message");
    add_exit(RDIR + "q11", "east", "@@leave_message");
    add_exit(RDIR + "passage3", "south", "@@end_message");
    reset_kendermore_room();
}

int
leave_message()
{
    write("You push aside the tapestry and stumble into a huge room.\n"); 
    return 0;
}

int
end_message()
{
    write("Cobwebs brush at your face as you make your way down " +
        "the long passageway. It seems to take a long time to " +
        "reach the end in this dim light, but finally you come to " +
        "a solid wall and an exit.\n");
    return 0;
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
        start_room_tells();
}

