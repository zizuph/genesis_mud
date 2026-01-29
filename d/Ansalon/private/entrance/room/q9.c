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
    set_short("A small dimly lit office");
    set_long("There isn't much here, just a desk, a chair, a rug and " + 
        "a large tapestry covering the back wall. Two torches are mounted " + 
        "on the north and south walls to give off a bit of light. There " + 
        "are no windows, but a slight breeze sends the torches flickering.\n");
    add_item(({"surface", "top"}), "It's clean and tidy.\n");
    add_item(({"west wall", "back wall", "tapestry", "large tapestry"}), 
        "This tapestry covers the entire west wall. It depicts a woodland " + 
        "scene with deer, rabbits, birds, squirrels, and other animals " + 
        "drinking from a clear lake. A hunter crouches in the bushes, " + 
        "aiming at one of the deer with a longbow. It looks like " + 
        "there's enough space for someone to move behind the tapestry.\n");
    add_item("desk", "It is large and sturdy, with a drawer on the left. " + 
        "Nothing lies on the surface of this desk. Its owner must be very " + 
        "tidy.\n");
    add_item("drawer", "It is large, and would slide open easily.\n");
    add_item("rug", "This rug is thick and red, and placed in front of " + 
        "the desk.\n");
    add_item("chair", "The chair is hard and uncomfortable.\n");
    add_item(({"hunter", "bushes"}), "The hunter is crouched in the bushes, " + 
        "trying to avoid being spotted by his skittish prey. His " + 
        "shoulder length black hair looks tangled and matted, and he " + 
        "is dressed in badly dented and rusting armour. His face " + 
        "bears the traces of nobility, but is gaunt from starvation.\n");
    add_item("longbow", "It looks barely adequate for hunting\n");
    add_item(({"deer", "rabbits", "birds", "squirrels", "animals",
        "other animals"}), "They are gathering at the lake for water. " + 
        "The animals look as if they might flee at the slightest sound.\n");
    add_item(({"lake", "clear lake"}), "Only slight ripples mar the " + 
        "surface of the crystal clear lake.\n");
    add_item(({"stone", "black stone", "rough stone", "rough black stone",
        "limestone"}),
        "Rough hewn blocks of limestone make up the walls, floors and " + 
        "ceiling of this hall.\n");
    add_item(({"wall", "walls", "stone wall",
        "stone walls", "rough wall",
        "rough walls", "rough stone wall", "rough stone walls",}), "They " + 
        "are made of limestone, and look very sturdy. Torches are " + 
        "mounted on the north and south walls, lighting the room with a " + 
        "dim eerie light. A large tapestry covers the west wall.\n");
    add_item(({"floor", "floors"}), "They are made of roughly cut " + 
        "limestone.\n");
    add_item(({"office", "room"}), "From its location, this office must " + 
        "belong to the dungeon master.\n");
    add_item("ceiling", "It is made of roughly cut limestone.\n"); 
    add_item(({"torch", "torches", "north wall", "south wall"}), "They are " + 
        "large tar-drenched torches that light the office.\n");
    add_item(({"eerie shadows", "shadows", "eerie shadow", "shadow"}),
        "You can't quite see into the darkest part of the shadowed " + 
        "room. This looks like an excellent place to sneak around.\n"); 

   set_tell_time(300);
    add_tell("The sound of something large moving to the south can " +
        "be heard.\n");
    add_tell("A chill in the air makes you shiver.\n");
    add_tell("The torches flicker, sending the shadows dancing.\n");
    add_tell("A rat moves around in the shadows.\n");
    add_tell("A spider scurries across the floor.\n");

    add_cmd_item(({"behind the tapestry", "behind tapestry" }), "move", "@@move_tapestry");
    add_cmd_item(({"drawer", "desk", "large drawer", "open drawer",
        "open desk", "open large drawer"}), ({"slide", "open"}),
        "@@slide_drawer");
    door = clone_object(ODIR + "qdoor4");
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

string
move_tapestry()
{
    write("You move behind the tapestry and find yourself in a " + 
        "secret passage, how exciting!\n");
    TP->move_living("behind the tapestry", RDIR + "passage", 0, 0);
    return "";
}

string
slide_drawer()
{
    object disk;
    if(!present("_blue_pass_medal_", TP))
    {
        disk = clone_object(ODIR + "disk");
        disk->move(TP);
        return("You slide open the desk drawer. You find a bunch of boring " + 
            "papers. Just as you're about to close the drawer, a round " + 
            "blue disk falls out from amidst the papers. You close the drawer " + 
            "again.\n");
    }
    else
    {
        return("You slide open the desk drawer. You find a bunch of " +
            "boring papers. You close the drawer again.\n");
    }
}

int
hall_message()
{
    write("The doors on each side of you call to your curiousity.\n");
    return 0;
}

