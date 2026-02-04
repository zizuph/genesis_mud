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
    set_long("This is a simple path. It runs to the northwest\n" +
             "and to the southeast. To the south is a forest of\n" +
             "large trees, to the north a copse of willows.\n");
    add_exit("/d/Terel/mecien/valley/path3", "southeast",0);
    add_exit("/d/Terel/mecien/valley/clearing", "south",0);
    add_exit("/d/Terel/mecien/valley/copse1", "north",0);
    add_exit("/d/Terel/mecien/valley/path5", "northwest",0);
}


