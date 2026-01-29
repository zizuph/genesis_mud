/*
 * This is just an example room to explain how the Long_Extra functionality
 * can work. 
 */
#pragma strict_types

inherit "/d/Sparkle/area/city/sewer/room/main_tunnel_base_gorboth";


/*
 * Function name:        create_tunnel_room
 * Description  :        set up the room with default presets,
 *                       and customize it as we desire.
 */
public void
create_tunnel_room()

{
    set_long_extra("Oooooo ... someone has made an example of this"
      + " room!");

    add_exit("example_room2", "north");
} /* create_tunnel_room */
