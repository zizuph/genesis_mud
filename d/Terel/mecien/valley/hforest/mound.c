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
    object bdoor1;

    set_short("Haunted Forest");
    set_long("This seems to be the center of the dark forest,\n" +
	     "in the midst of which is a large earthen mound.\n");
    bdoor1=clone_object("/d/Terel/mecien/valley/hforest/bdoor1");
    bdoor1->move(this_object());
    bdoor1->set_key(0006000);

    add_exit("/d/Terel/mecien/valley/hforest/forest1", "south", 0);
    add_exit("/d/Terel/mecien/valley/hforest/forest3", "east", 0);
    add_exit("/d/Terel/mecien/valley/hforest/forest4", "west", 0);
    add_exit("/d/Terel/mecien/valley/hforest/forest2", "north", 0);
    add_item( ({ "mound" , "barrow" }) , 
	      "The great mound is made of packed earth and layers of stone.\n");

}

/*
 * Function name:
 * Description  :
 */

