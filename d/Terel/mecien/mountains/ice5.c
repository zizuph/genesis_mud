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
    set_long("This is the high parts of the vast mountain chain,\n" +
             "from here you can see out across the land. Far to the\n" +
	     "north there seems to be a great cavern.\n");
        add_exit("/d/Terel/mecien/mountains/ice6", "north",0);
        add_exit("/d/Terel/mecien/mountains/ice2", "south", 0);
        add_exit("/d/Terel/mecien/mountains/ice7", "east",0);
}

/*
 * Function name:
 * Description  :
 */

