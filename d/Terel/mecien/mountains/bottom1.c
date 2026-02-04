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

    set_short("Cavern");
    set_long("This cavern reeks of death, bones are strewn about the\n" +
             "ground. A large puddle lies here, dark and fetid. There\n" +
	     "is ash all about.\n");
    add_exit("/d/Terel/mecien/mountains/hole", "up",0);
    add_exit("/d/Terel/mecien/mountains/bottom2", "south", 0);
}

/*
 * Function name:
 * Description  :
 */

