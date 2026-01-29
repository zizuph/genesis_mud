/* room1.c
   Mort 911004 */

inherit "/std/room";

/*
 * Function name: create_room()
 * Description  : Create the room.
 * In this function, we declare everything that should be fixed
 * when the room is started, and not changed in resets.
 */

create_room() {

    set_short("A Dark Hall");
    set_long("A darkened hall, with a large stone chair.\n");
    add_exit("/d/Terel/mecien/mchamber", "stair",0);

}

/*
 * Function name:
 * Description  :
 */

