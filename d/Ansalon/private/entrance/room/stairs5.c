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
    set_short("The bottom of a dimly lit stone stairway");
    set_long("You are standing at the bottom of a dimly lit stone stairway. " + 
        "Torches are " + 
        "mounted on the walls at regular intervals. They flicker, " + 
        "throwing eerie shadows. A dark stair winds up into " + 
        "the darkness.\n");
    add_item("stair", "It winds up beyond your view into the " + 
        "darkness. Who knows where it leads, but it looks exciting! " + 
        "The steps look old and crumbly.\n");
    add_item(({"stone", "rough stone", "limestone"}),
        "Rough hewn blocks of limestone make up the walls, floors and " + 
        "ceiling of this stairway and hall.\n");
    add_item(({"wall", "walls", "stone wall",
        "stone walls", "rough wall",
        "rough walls", "rough stone wall", "rough stone walls",}), "They " + 
        "are made of limestone, and look very sturdy. Torches are " + 
        "mounted on them, lighting the stairway and hall with a dim " + 
        "eerie light.\n");
    add_item(({"floor", "floors"}), "They are made of roughly cut " + 
        "limestone.\n");
    add_item(({"steps", "step"}), "Considering their age, the steps " + 
        "are holding up surprisingly well. However, they are crumbling " + 
        "in certain spots.\n");
    add_item("ceiling", "It is made of roughly cut limestone.\n"); 
    add_item(({"torch", "torches"}), "They are large tar-drenched " + 
        "torches that light the stairway.\n");
    add_item(({"eerie shadows", "shadows", "eerie shadow", "shadow"}),
        "You can't quite see into the darkest part of the shadows. " + 
        "This looks like an excellent place to sneak around.\n"); 
    set_tell_time(300);
    add_tell("The sound of something large moving below you can be heard.\n");
    add_tell("A chill in the air makes you shiver.\n");
    add_tell("The torches flicker, sending the shadows dancing.\n");
    add_tell("A rat moves around in the shadows.\n");
    add_tell("A spider scurries across the floor.\n");
    add_tell("A part of the stairs crumbles a bit under your weight.\n");

    add_exit(RDIR + "stairs4", "down", "@@stair_message");
    add_exit(RDIR + "tower", "east", "@@tower_message");
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
tower_message()
{
    if (present("_blue_pass_medal_", TP))
    {
        write("The blue disk hums softly as you pass through the doorway.\n");
        return 0;
    }

    else
    {
        write("You see a blue flash as you try to pass through the door. " + 
            "a strong force knocks you back. A voice whispers in your " + 
            "head, 'Only one who has the disk may pass.'\n");
        return 1;
    }
}

int
stair_message()
{
    write("Your steps echo into the darkness as you descend.\n");
    return 0;
}
