/* room2.c
   Mort 911004 */

inherit "/std/room";
#include "defs.h";

/*
 * Function name: create_room()
 * Description  : Create the room.
 * In this function, we declare everything that should be fixed
 * when the room is started, and not changed in resets.
 */

reset_room(arg){
object faun;
if(!present("faun")){
faun=clone_object(PATH + "faun");
faun->move(this_object());
}
}

create_room() {

    set_short("Forest");
    set_long("A forest of immense trees. Grand oaks, stately birch,\n" +
             "elm and maples, and elegant pine. There is little or no\n" +
     "underbrush. The canopy is alive with life.\n");

add_item("canopy", "It is full of vibrant life. It is the fragrant power of\n"
   + "of the midsummer, enchanted lives and begotten mysteries.\n");
  add_item("tree", "They are countless and ageless. They are full strength\n"
  + "in this seeming summer, a strange and timeless power.\n");
  add_item("oaks", "They are grand trees, the elders of the forest. In them\n"
  + "is wisdom and strength.\n");
  add_item("birch", "Stately and royal are these white clad trees. A power\n"
  + "and beauty all their own.\n");
 add_item("elm", "Shady and quiet, these trees are both beautiful and strong,\n"
  + "provong the life of simplicity.\n");
  add_item("maple", "Kind and gentle, these strong trees, some red and others plain in their\n"
  + "vibrant green. They cast forth their seeds like gifts of\n"
  + "joy to the world.\n");
add_item("pines", "Peaceful these sweet conifers. They are the whispers\n"
  + "of the forest, the lorist of the ages.\n");

   add_exit(MAZE, "north", 0);
   add_exit(MAZE, "south", 0);
  add_exit(MAZE, "east", 0);
   add_exit(MAZE, "west", 0);

reset_room();
}

/*
 * Function name:
 * Description  :
 */

