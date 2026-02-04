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
    set_long("This seems to be the center of the mountain chain, the\n" +
             "icy cliffs rising up to the east and west, permitting travel\n" +
	     "only north and south. To the south stairs have been carved\n" +
             "in the ice, making the upward climb easier.\n");
    add_exit("/d/Terel/mecien/mountains/ice11", "north",0);
    add_exit("/d/Terel/mecien/mountains/ice8", "south",0);
}

/*
 * Function name:
 * Description  :
 */

