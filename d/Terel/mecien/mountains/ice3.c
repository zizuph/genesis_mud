/* room2.c
   Mort 911004 */

inherit "/std/room";

/*
 * Function name: create_room()
 * Description  : Create the room.
 * In this function, we declare everything that should be fixed
 * when the room is started, and not changed in resets.
 */

create_room() {

    set_short("Ice Mountains");
    set_long("This is the high parts of the icy mountains, here\n" +
             "the snow is not so deep. Rocks jut out from the banks\n" +
	     "of snow, exposing cliff walls. There seems to be a cave\n" +
             "to the northwest\n");
        add_exit("/d/Terel/mecien/mountains/cave", "northwest",0);
        add_exit("/d/Terel/mecien/mountains/ice2", "east",0);
        add_exit("/d/Terel/mecien/mountains/gap", "south", 0);
}

/*
 * Function name:
 * Description  :
 */

