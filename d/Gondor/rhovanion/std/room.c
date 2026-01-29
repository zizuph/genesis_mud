/*
 * /d/Gondor/rhovanion/std/room.c
 *
 * Default base room for the Rhovanion domain. All rooms should use this
 * instead of /std/room, and redefine create_rhovanion_room instead of
 * create_room. This allows addition of default functionality in all of 
 * the Rhovanion rooms.
 *
 * Created by Eowul, Juni 29th, 2008
 */
 
inherit "/std/room";
inherit "/d/Gondor/common/lib/time.c";

/*
 * Function name: create_rhovanion_room
 * Description  : Construct the room
 */
void create_rhovanion_room() 
{
}

/*
 * Function name: create_room
 * Description  : Constructs a default room, will call the Rhovanion
 *              : specific constructor.
 */
void create_room()
{
    create_rhovanion_room();
}

/*
 * Function name: init
 * Description  : Add commands to the player
 */
void init() 
{
    ::init();
    add_action(check_time, "time");
}