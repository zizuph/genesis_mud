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
    set_long("This is a simple path that leads north and\n" +
             "south. To the west lies a great forest. A grove\n" +
	     "of thorns makes travel east impossible.\n");

   add_item(({"grove", "thorns"}), "They are thick and spread northwards.\n");
    add_exit("/d/Terel/mecien/valley/path3", "north",0);
    add_exit("/d/Terel/mecien/valley/path1", "south",0);
    add_exit("/d/Terel/mecien/valley/forest2", "west", 0);
}

/*
 * Function name:
 * Description  :
 */

