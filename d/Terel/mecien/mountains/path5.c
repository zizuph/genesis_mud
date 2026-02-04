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
    set_long("A small path runs north along the steppes of the\n" +
             "mountains that form the western border of the valley.\n" +
             "The path turns here to the southeast, towards a large\n" +
             "forest. Thre is a hilltop south of here.\n");
    add_exit("/d/Terel/mecien/valley/path4", "southeast",0);
    add_exit("/d/Terel/mecien/valley/hilltop", "south",0);
    add_exit("/d/Terel/mecien/valley/path5", "north",0);
}


