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
    set_long("This is a path leading north to an ominous city that looks\n" +
             "to be in a state of ruin. South it follows the steppes of the\n" +
             "mountains that form the west border of the valley. The sky is\n" +
             "dark, ready to storm. To the east is a forest.\n");
    add_exit("/d/Terel/mecien/valley/city/gates", "north",0);
    add_exit("/d/Terel/mecien/valley/path7", "south",0);
    add_exit("/d/Terel/mecien/valley/fall/forest2", "east",0);
}


