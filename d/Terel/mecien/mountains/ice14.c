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
"way difficult for travel. There is a burrow here into the snow.\n");
    add_exit("/d/Terel/mecien/mountains/ice6", "south", 0);
   add_item("burrow", "It goes down into the snow.\n");
   add_exit("/d/Terel/mecien/mountains/clair", "down", 0);
}

/*
 * Function name:
 * Description  :
 */

