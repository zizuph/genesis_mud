/* room2.c
   Mort 911004 */
#define PATH "/d/Terel/mecien/mountains"
inherit "/std/room";

/*
 * Function name: create_room()
 * Description  : Create the room.
 * In this function, we declare everything that should be fixed
 * when the room is started, and not changed in resets.
 */

create_room() {

    set_short("Pass");
    set_long("This is a small pass in the ice that leads south\n" +
	     "into a large cavern and north to the steppes of the\n" +
             "ice mountains.\n");

    add_exit("/d/Terel/mecien/mountains/ice1", "north",0);
    add_exit("/d/Terel/mecien/mountains/cavern", "south",0);

}

/*
 * Function name:
 * Description  :
 */

