

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
    set_long("Here a gap is open in the mountains, it opens a way south\n" +
             "to a ridge and north to the deeper parts of the mountains.\n" +
	     "Shadows hang on the southern horizon.\n");
        add_exit("/d/Terel/mountains/ice3", "north",0);
        add_exit("/d/Terel/mountains/ridge", "south", 0);
}

/*
 * Function name:
 * Description  :
 */

