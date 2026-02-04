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
    set_long("This is a simple path that travels between two\n" +
             "forests, it leads north. To the west is a great\n" +
	     "forest of magnificent trees. The forest to the east\n" +
             "is filled with thorns and briars making it unpassable.\n");
   add_item("thorns", "It is a huge grove that spreads northwards.\n");
    add_exit("/d/Terel/mecien/valley/path2", "north",0);
    add_exit("/d/Terel/mecien/valley/wlanding", "southeast",0);
    add_exit("/d/Terel/mecien/valley/forest1", "west", 0);
}

/*
 * Function name:
 * Description  :
 */

