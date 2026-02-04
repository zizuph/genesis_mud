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

    set_short("Ice Tunnel");
    set_long("This is a massive tunnel that has somehow been carved into\n" +
	     "the ice. Its walls are smooth and cylindrical.\n");
    add_exit("/d/Terel/mecien/mountains/tunnel2", "south", 0);
    add_exit("/d/Terel/mecien/valley/entrance", "north", 0);

}

/*
 * Function name:
 * Description  :
 */

