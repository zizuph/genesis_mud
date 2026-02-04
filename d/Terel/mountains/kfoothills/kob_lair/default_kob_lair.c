/*
 *  default_kob_lair.c
 *
 *  Britanica 160322
 */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "include/cave_defs.h"

inherit STDROOM;
inherit "/d/Terel/std/room_tell.c";

/*
 * Function name: init
 * Description:   Add the 'command items' of this object. 
 */
public void
init()
{
    ::init();
    start_room_tells();
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    INSIDE;
    set_short("Natural cave");
    set_long("The natural cave has uneven walls that are have been "+
        "smoothed by the passage of time. Small smooth rocks litter " +
        "the floor of the cave.\n");
    add_item(({"wall","walls"}),
        "The uneven walls contains many cracks and ledges worn smooth by " +
        "passage of time.\n");
    add_item(({"crack","cracks", "ledge", "ledges"}),
        "The cave walls contains many cracks and ledges.\n");
    add_item(({"rock", "rocks", "small rocks"}), "Small rocks litter the " +
        "floor of the cave.\n");
        
    set_tell_time(100 + random(200));
     
    add_tell("The sound of a drip echoes in the distance.\n");
    add_tell("A breeze blows past carrying a vile stench.\n");
    add_tell("You hear scuffling sound nearby.\n");
    
}