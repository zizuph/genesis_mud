/* /d/Faerun/guilds/fire_knives/rooms/council-post.c
 *
 * A mail room for the council only.
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

    set_short("A Quiet Room");
    
    set_long("The room is small compared to the others, and simple in its "
    + "adornments. A simple chair is placed by a writing desk upon which "
    + "you can write and read copies of your missives kept within the slots "
    + "on the dark walls.\n");   

    add_item(({"room"}),
    "You are within it.\n");
    
    add_item(({"walls", "wall"}),
    "The walls are dark and bare of adornments. Cracks within it seem to "
    +"disappear into nothingness.\n");
    
    add_item(({"crack","cracks", "holes", "hole"}),
    "The cracks seem to lead into nothingness.\n");
    
    add_item(({"chair"}),
    "A simple wooden chair by a writing desk upon which you can sit to write "
    +"and read your missives.\n");
    
    add_item(({"desk"}),
    "The desk is a simple one meant for composing and reading mail.\n");

    add_exit(FIREKNIVES_ROOMS_DIR + "reception", "southwest");

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
