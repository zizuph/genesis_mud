

/* room2.c
   Mort 911004 */
#define PATH "/d/Terel/mountains/obj"
inherit "/std/room";

/*
 * Function name: create_room()
 * Description  : Create the room.
 * In this function, we declare everything that should be fixed
 * when the room is started, and not changed in resets.
 */

create_room() {
    object door;

    set_short("Icy Canyon");
    set_long("This is a small icy canyon, in the midst of which\n" +
	     "is a large stone house. The roof is made of thatch.\n");

    door = clone_object(PATH + "/hdoor");
    door->move(this_object());

    add_exit("/d/Terel/mountains/ice9", "south",0);
    add_item( ({ "house", "stone house" }) , 
	      "It seems to have been made by giants.\n");

}

/*
 * Function name:
 * Description  :
 */

