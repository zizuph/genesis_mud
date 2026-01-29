inherit "/std/room";
inherit "/d/Faerun/std/room_tell";
/*
 * Function name: create_room()
 * Description  : Create the room.
 * In this function, we declare everything that should be fixed
 * when the room is started, and not changed in resets.
 */

create_room()
{

    set_short("A simple room");
    set_long("You find yourself in a very simple room. This is a example of a room that sends room tells.\n");


// tells the room how often to send a room tell in seconds
    set_room_tell_time(30);


// The room tells/messages players see. Notice there isn't a \n at 
// the end of the message
    add_room_tell("Some villagers walk past you.");
    add_room_tell("A pink elephant waltzes by.");
    add_room_tell("A breeze blows past you.");
}


/*
 * Function name : enter_inv 
 * Description   : sman enter_inv for more details.  It's masked here
 *                 for room_tell support.
 */
public void
enter_inv(object ob, object from)
{
    if (sizeof(query_room_tells()))
    start_room_tells();
    ::enter_inv(ob,from);
}