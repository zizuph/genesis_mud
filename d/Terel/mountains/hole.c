

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

    set_short("Black Hole");
    set_long("Here in the midst of the mountains, a large black hole\n" +
             "opens down into the earth. The hole seems to have been\n" +
	     "melted into the ice by some extreme heat.\n");
    add_exit("/d/Terel/mountains/ice8", "north",0);
    add_exit("/d/Terel/mountains/bottom1", "down", 0);
}

/*
 * Function name:
 * Description  :
 */

