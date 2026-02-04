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
    set_long("The mountains here are very pointed, unnaturally it\n" +
             "seems. Icy cliffs rise up to the east and west making travel\n" +
	     "possible only to the north and south. A great cylindrical\n" +
             "tunnel leads into the depths of the icy north mountain.\n");
    add_exit("/d/Terel/mecien/mountains/tunnel", "north",0);
    add_exit("/d/Terel/mecien/mountains/ice11", "south",0);
}

/*
 * Function name:
 * Description  :
 */

