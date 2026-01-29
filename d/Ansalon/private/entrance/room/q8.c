#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include "/d/Ansalon/goodlund/kendermore/local.h"

inherit KENDERMORE_IN;

#define ODIR      "/d/Ansalon/private/entrance/obj/"
#define RDIR      "/d/Ansalon/private/entrance/room/"
#define NDIR      "/d/Ansalon/private/entrance/npc/"

object door, evil_mage;

void
reset_kendermore_room()
{
    if (!objectp(evil_mage))
    {
        evil_mage = clone_object(NDIR + "shunar");
        evil_mage->move(TO);
    }
}

void
create_kendermore_room()
{
    set_short("A dimly lit stone hall");
    set_long("You are standing in a dimly lit stone hall. Rows of " + 
        "black metal doors stand along the west wall to the south. Torches " + 
        "are mounted on the walls at regular intervals. They flicker, " + 
        "throwing eerie shadows. A dark stair leads down to your north, " + 
        "and the hallway continues into the darkness to your south. " + 
        "You spot some dusty footprints on the floor.\n");
    add_item("stair", "It leads into the darkness to your south. Who " + 
        "knows where it leads!\n");
    add_item(({"stone", "black stone", "rough stone", "rough black stone",
        "limestone"}),
        "Rough hewn blocks of limestone make up the walls, floors and " + 
        "ceiling of this hall.\n");
    add_item(({"wall", "walls", "stone wall",
        "stone walls", "rough wall",
        "rough walls", "rough stone wall", "rough stone walls",}), "They " + 
        "are made of limestone, and look very sturdy. Torches are " + 
        "mounted on them, lighting the hallway with a dim eerie light.\n");
    add_item(({"floor", "floors"}), 
        "The floor is made of roughly cut limestone. There are some " + 
        "footprints here.\n"); 
    add_item(({"footprints", "dusty footprints"}), "The footprints were " + 
        "made by heavy booted feet, going in and out of the door to " + 
        "the west.\n");
    add_item("ceiling", "It is made of roughly cut limestone.\n"); 
    add_item(({"torch", "torches"}), "They are large tar-drenched " + 
        "torches that light the hallway.\n");
    add_item(({"eerie shadows", "shadows", "eerie shadow", "shadow"}),
        "You can't quite see into the darkest part of the shadowed " + 
        "hall. This looks like an excellent place to sneak around.\n"); 
    add_item(({"rows", "doors", "west wall"}), "This hallway doesn't look " + 
        "like a dungeon. The doors must lead into more civilized chambers.\n");

    set_tell_time(300);
    add_tell("The sound of something large moving to the south can " +
        "be heard.\n");
    add_tell("A chill in the air makes you shiver.\n");
    add_tell("The torches flicker, sending the shadows dancing.\n");
    add_tell("A rat moves around in the shadows.\n");
    add_tell("A spider scurries across the floor.\n");

    add_exit(RDIR + "stairs2", "north", "@@stair_message");
    add_exit(RDIR + "q10", "south", "@@hall_message");
    door = clone_object(ODIR + "qdoor4b");
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

int
stair_message()
{
    write("Your steps echo into the darkness.\n");
    return 0;
}
