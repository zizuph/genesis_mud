

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

    set_short("Cellar");
    set_long("A shadowy cellar, frosted over with a slick sheet\n" +
	     "of ice, blotted with patches of spilled wine. Large\n" +
             "casks of wine are stacked here, too big to be moved.\n");

    door = clone_object(PATH + "/cdoor1.c");
    door->move(this_object());

    add_exit("/d/Terel/mountains/house4", "up",0);
    add_item( ({ "casks", "wine" }) , 
	      "It is a very cheap wine and the casks are somewhat rotted.\n");

}

/*
 * Function name:
 * Description  :
 */

