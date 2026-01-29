#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include "/d/Ansalon/goodlund/kendermore/local.h"

inherit KENDERMORE_IN;

#define ODIR      "/d/Ansalon/private/entrance/obj/"
#define NDIR      "/d/Ansalon/private/entrance/npc/"
#define RDIR      "/d/Ansalon/private/entrance/room/"

object door;

void
reset_kendermore_room()
{
}

void
create_kendermore_room()
{
    set_short("");
    set_long("This is an empty chamber before a stairway, being " + 
        "decorated only by two torches, a tapestry on the " + 
        "west wall and stone. The stairway lies to the south, while a door " + 
        "is set in the east wall.\n");
    add_item("east wall", "A door is set in the east wall.\n");
    add_item(({"west wall", "back wall", "tapestry", "large tapestry"}),
        "This tapestry covers the entire west wall. It depicts a fierce " +
        "battle between two warriors. The two are surrounded by flames, " + 
        "arrows and the rage of battle, but the two seem completely " + 
        "oblivious to their surroundings. It looks like " +
        "there's enough space for someone to move behind the tapestry.\n");
    add_item("warriors", "One warrior stands in a defensive posture, " + 
        "staring at his opponent in a mixture of horror and sadness. The " + 
        "other stands ready to lunge, a look of madness and hatred burning " + 
        "in his eyes.\n");
    add_item(({"stair", "stairway", "south wall"}), "The stairway " + 
        "winds up into the darkness to the south.\n");
    add_item(({"torch", "torches"}), "They are large tar-drenched " +
        "torches that light the chamber.\n");
    add_item(({"stone", "rough stone", 
        "limestone"}),
        "Rough hewn blocks of limestone make up the walls, floors and " + 
        "ceiling of this chamber.\n");
    add_item(({"wall", "walls", "stone wall",
        "stone walls", "rough wall",
        "rough walls", "rough stone wall", "rough stone walls"}), "They are " + 
        "made of limestone. Torches are " +
        "mounted on the north and south walls, lighting the room with a " +
        "dim eerie light. A large tapestry covers the west wall.\n");
    add_item(({"floor", "floors"}), "They are made of limestone.\n"); 
    add_item("ceiling", "It is made of roughly cut limestone.\n");        
    add_cmd_item("behind tapestry", "move", "@@move_tapestry");

    set_tell_time(300);
    add_tell("The sound of something large moving to the north can " +
        "be heard.\n");
    add_tell("A chill in the air makes you shiver.\n");
    add_tell("The torches flicker, sending the shadows dancing.\n");
    add_tell("A rat moves around in the shadows.\n");
    add_tell("A spider scurries across the floor.\n");

    add_exit(RDIR + "stairs3", "south", "@@stair_message");
    door = clone_object(ODIR + "qdoor6");
    door->move(TO);
    reset_kendermore_room();
}

string
move_tapestry()
{
    TP->move_living("behind the tapestry", RDIR + "passage3", 0, 1);
    return ("You move behind the tapestry and find yourself in a " +
        "secret passage, how exciting!\n");
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
        start_room_tells();
}

int
stair_message()
{
    write("The first step crumbles under your foot, and you stumble " + 
        "slightly before catching your balance again. You stop briefly " + 
        "as you hear what sounds like the sounds of laughter, but " + 
        "continue on when silence surrounds you.\n");
}
