

inherit "/std/room";
#include <stdproperties.h>

#define NUM 1

object ogre; /* Make this a global variable to keep track of ogre. */

reset_room(arg){
 int i;
/* I cut this part out, no good. 
 object ogre;
 ogre=allocate(NUM);
 if(present("ogre")) return;
*/
 for(i=0; i<NUM; i++){
  if (!ogre[i])
  {
   ogre[i]=clone_object("/d/Terel/mountains/obj/ogre");
   ogre[i]->move(this_object());
  }
 }
}

create_room(){
ogre = allocate(NUM); /* This should be done once. */
set_short("Main Hall");
set_long(
"This is the main hall of the house. In the center of the room is a\n"
+"large table with chairs. The floor is littered with scraps of food\n"
+"and spilled drink. There are open doors in all directions.\n"
);
add_prop(ROOM_I_INSIDE, 1);
add_exit("/d/Terel/mountains/house1","south",0);
add_exit("/d/Terel/mountains/house4","north",0);
add_exit("/d/Terel/mountains/house3","east",0);
add_exit("/d/Terel/mountains/kitchen","west",0);
add_item(({"table","chairs"}),
"The table and chairs are large, but one chair is huge!\n"
);
reset_room();
}
