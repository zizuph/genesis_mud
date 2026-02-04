/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
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

    set_short("Ancient Stair");
    set_long("Hewn from the mountain steppes, these ancient steps\n" +
             "ascend into the cloudy heights. Below to the east the\n" +
	     "forests of the valley can be seen, in the midst of the\n" +
             "valley a lake. The top of the stairs can be seen higher\n" +
             "up to the west, a strange structure is there.\n");
    add_exit("/d/Terel/mecien/valley/guild/stair1", "east",0);
    add_exit("/d/Terel/mecien/valley/guild/stair3", "west", 0);
}

/*
 * Function name:
 * Description  :
 */

