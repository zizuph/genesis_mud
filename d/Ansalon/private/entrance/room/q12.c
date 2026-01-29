#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include "/d/Ansalon/goodlund/kendermore/local.h"

inherit KENDERMORE_IN;

#define ODIR      "/d/Ansalon/private/entrance/obj/"
#define RDIR      "/d/Ansalon/private/entrance/room/"

object door;

void
reset_kendermore_room()
{
}

void
create_kendermore_room()
{
    set_short("A dimly lit stone hall");
    set_long("You are standing in a dimly lit stone hall. Rows of " + 
        "black metal doors stand along the west wall to the north " + 
        "Torches " + 
        "are mounted on the walls at regular intervals. They flicker, " + 
        "throwing eerie shadows. " + 
        "The hallway continues into the darkness to your north.\n"); 
    add_item(({"stone", "black stone", "rough stone", "rough black stone",
        "limestone"}),
        "Rough hewn blocks of limestone make up the walls, floors and " + 
        "ceiling of this hall.\n");
    add_item(({"wall", "walls", "stone wall",
        "stone walls", "rough wall",
        "rough walls", "rough stone wall", "rough stone walls",}), "They " + 
        "are made of limestone, and look very sturdy. Torches are " + 
        "mounted on them, lighting the hallway with a dim eerie light.\n");
    add_item(({"floor", "floors"}), "They are made of roughly cut " + 
        "limestone.\n");
    add_item("ceiling", "It is made of roughly cut limestone.\n"); 
    add_item(({"torch", "torches"}), "They are large tar-drenched " + 
        "torches that light the hallway.\n");
    add_item(({"eerie shadows", "shadows", "eerie shadow", "shadow"}),
        "You can't quite see into the darkest part of the shadowed " + 
        "hall. This looks like an excellent place to sneak around.\n"); 
    add_item(({"rows", "doors", "west wall"}), "This hallway doesn't look " + 
        "like a dungeon. The doors must lead into more civilized chambers.\n");

    set_tell_time(300);
    add_tell("The sound of something large moving to the north can " +
        "be heard.\n");
    add_tell("A chill in the air makes you shiver.\n");
    add_tell("The torches flicker, sending the shadows dancing.\n");
    add_tell("A rat moves around in the shadows.\n");
    add_tell("A spider scurries across the floor.\n");

    add_exit(RDIR + "q10", "north", "@@hall_message");
    door = clone_object(ODIR + "qdoor6b");
    door->move(TO);
    reset_kendermore_room();
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
        start_room_tells();
}

int
hall_message()
{
    write("The doors on each side of you call to your curiousity.\n");
    return 0;
}
