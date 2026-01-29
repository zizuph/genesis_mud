/* /d/Faerun/guilds/fire_knives/rooms/po.c
 *
 * Post Office for full members
 *
 * Nerull 2019
 *
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";

inherit FIREKNIVES_STD_ROOM;
inherit "/d/Genesis/lib/post";


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_fireknives_room()
{
    add_prop(ROOM_I_INSIDE, 1);

     set_short("Writing room");
     
    set_long("Within the small, narrow room there is "
    +"nothing but a simple wooden "
    +"desk facing the southern wall. All others "
    +"are covered in large locker-like "
    +"compartments in which missives are kept, "
    +"properly labeled with square plaques "
    +"that have names carved on them. Slightly "
    +"above eye level on top of the desk "
    +"is a rectangular orifice through which "
    +"letters can be deposited to be sent "
    +"to their marked destinations. All around "
    +"the chamber reigns an aura of silence "
    +"an peace which serves the purpose of focusing on the task at hand. \n");
     
    add_item(({"room","area","chamber"}),
    "The chamber is small and narrow, serving a "
    +"single purpose and decorated to that "
    +"end.\n");
 
    add_item(({"desk","wooden desk"}),
    "The desk faces the southern wall, providing a "
    +"comfortable space to sit down and "
    +"pen a missive or read received ones. It's "
    +"structure doesn't invite to long periods "
    +"of rest.\n");
 
    add_item(({"walls"}),
    "The walls are bare, devoid of any distracting "
    +"decorations other than the functional "
    +"compartments embedded on them where letters "
    +"are stored and retrieved from. The "
    +"southern one is devoid even of that, containing "
    +"only a small rectangular orifice.\n");
 
    add_item(({"southern wall"}),
    "The southern wall is of simple stone cut and "
    +"polished over time. It's only distinguishing "
    +"trait being the rectangular orifice slightly "
    +"above eye level of someone sitting at the "
    +"desk.\n");
 
    add_item(({"compartments","lockers","containers"}),
    "The compartments are made of a sturdy metal, closed "
    +"and marked each with a different "
    +"name. Yours is perceived from here at the "
    +"end of one of the rows.\n");
 
    add_item(({"plaques","names"}),
    "There is a plaque on each one of the compartments "
    +"lining up the walls upon which the "
    +"names are carved.\n");
 
    add_item(({"orifice","rectangular orifice"}),
    "The rectangular orifice is slightly above eye "
    +"level from someone sitting at the desk. "
    +"You cannot see anything inside, but by its size "
    +"and context you can tell that you "
    +"could place a missive through it for delivery.\n");
 
    add_item(({"ceiling"}),
    "The ceiling is high up and lost in the "
    +"darkness that engulfs it, its only connection "
    +"to the rest of the room being the walls that "
    +"aim to reach towards it.\n");
 
    add_item(({"floor"}),
    "The floor is cold and bare, devoid of any "
    +"decorative or functional items covering "
    +"it, making any sitting down at the desk "
    +"for longer periods of time rather "
    +"uncomfortable.\n");

    add_item(({"chair"}),
    "The chair is a simple wooden one, standing in "
    +"front of the desk and used to write "
    +"down letters at it.\n");

    add_exit(FIREKNIVES_ROOMS_DIR + "o5", "north");

    reset_faerun_room();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}


void
init()
{
    ::init();
    post_init();
}


void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    post_leave_inv(ob, to);
}

