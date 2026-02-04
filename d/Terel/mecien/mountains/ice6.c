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
    set_long("Icy mountains fan out in all directions, cold winds\n" +
             "come down from the north. The snow is deep, making the\n" +
	     "way difficult for travel.\n");
    add_exit("/d/Terel/mecien/mountains/ice8", "west",0);
    add_exit("/d/Terel/mecien/mountains/ice5", "south", 0);
    add_exit("/d/Terel/mecien/mountains/cliff", "east", 0);
   add_exit("/d/Terel/mecien/mountains/ice14", "north", 0);
}

/*
 * Function name:
 * Description  :
 */

