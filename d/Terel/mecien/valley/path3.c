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
    set_long("This is a simple path that forks to the east,\n" +
             "northwest and south. To the southwest is a forest.\n");
    add_exit("/d/Terel/mecien/valley/path4", "northwest",0);
    add_exit("/d/Terel/mecien/valley/path2", "south",0);
    add_exit("/d/Terel/mecien/valley/end", "east",0);
    add_exit("/d/Terel/mecien/valley/edge", "southwest",0);
}

/*
 * Function name:
 * Description  :
 */

