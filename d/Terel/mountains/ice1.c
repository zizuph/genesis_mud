

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
    set_long("This is the lower steppes of a great chain of ice\n" +
             "covered mountains, which reach out in all directions.\n" +
	     "A path leads down to the east and higher to the north.\n");
    add_exit("/d/Terel/mountains/ice2", "north",0);
    add_exit("/d/Terel/mountains/pass", "south",0);
    add_exit("/d/Terel/common/road/road8", "east", 0);
}

/*
 * Function name:
 * Description  :
 */

