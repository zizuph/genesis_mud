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
    set_long("This pass winds up and down the dark mountains, dug into\n" +
             "it like a channel. The wind is filled with a black coal like\n" +
             "powder and ice. There are dead trees here.\n");
        add_exit("/d/Terel/mecien/mountains/dark2", "down",0);
        add_exit("/d/Terel/mecien/mountains/dcliff", "up", 0);

    add_item(({"tree", "trees"}), "They have been dead for some time.\n");
}

/*
 * Function name:
 * Description  :
 */

