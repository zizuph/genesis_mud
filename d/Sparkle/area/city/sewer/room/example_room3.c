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
    set_long_extra("Alas, it seems the example has come to an end.");

    add_exit("example_room2", "south");
} /* create_tunnel_room */
