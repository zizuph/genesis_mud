

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

    set_short("Dark Mountains");
    set_long("This is the base of a small group of mountains that\n" +
             "stand as dismal and dreery as anything nature could\n" +
	     "muster. The sides of the mountains are coated with\n" +
             "patches of dark rock, dead trees and spires of ice.\n" +
             "Unnatural clouds hang over these mountains, they display\n" +
             "flashes of lightning and cast forth bits of ice.\n" +
             "There is a pass leading up.\n");
        add_exit("/d/Terel/mountains/vale", "north",0);
        add_exit("/d/Terel/mountains/dark2", "up", 0);
}

/*
 * Function name:
 * Description  :
 */

