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

    set_short("Path");
    set_long("This is a small path running north-south along the\n" +
             "steppes of the mountains that form the western border\n" +
             "of the valley. The sky is darker northward. There is a\n" +
             "forst east of here, it seems to be in the midst of fall.\n");
    add_exit("/d/Terel/mecien/valley/path6", "north",0);
    add_exit("/d/Terel/mecien/valley/path5", "south",0);
    add_exit("/d/Terel/mecien/valley/fall/forest1", "east",0);
}


