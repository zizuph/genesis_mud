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
    set_long("This is the lower part of a great summit. Steps have\n" +
             "been carved in the ice that lead down from here to the\n" +
	     "north. The wind here is strangely calm. The summit rises\n" +
             "into the misty sky.\n");
        add_exit("/d/Terel/mecien/mountains/hole", "south", 0);
        add_exit("/d/Terel/mecien/mountains/ice6", "east",0);
   add_exit("/d/Terel/mecien/mountains/ice13", "west", 0);
/*
        add_exit("/d/Terel/mecien/mountains/summit", "up",0);
    add_exit("/d/Terel/mecien/mountains/ice10", "north", 0);
*/
}

/*
 * Function name:
 * Description  :
 */

