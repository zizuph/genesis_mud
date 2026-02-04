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

    set_short("Dark Mountains");
    set_long("A cliff standing out in the midst of the dark mountains,\n" +
             "exposed to the savage wind. An opening leads into the\n" +
             "depths. Not far above is the mountain's top.\n");
        add_exit("/d/Terel/mecien/mountains/dark3", "down",0);
        add_exit("/d/Terel/mecien/mountains/top", "up", 0);
        add_exit("/d/Terel/mecien/mountains/dcave", "in", 0);
/*
   add_exit("/d/Terel/mecien/mountains/etemp1", "pass", 0);
*/

}

/*
 * Function name:
 * Description  :
 */

