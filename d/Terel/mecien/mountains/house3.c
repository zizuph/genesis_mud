inherit "/std/room";
#include <stdproperties.h>

#define NUM 3

reset_room(arg){
 object *ogre;
 int i;
 ogre=allocate(NUM);
 if(present("ogre")) return;
 for(i=0; i<NUM; i++){
  ogre[i]=clone_object("/d/Terel/mecien/mountains/ogre");
  ogre[i]->move(this_object());
 }
}

create_room(){
set_short("Chamber");
set_long(
"This is a large bed chamber. There are four unkept beds here, all\n"
+"of which smell horrible. Terrible smells come from a hole in the\n"
+"floor. A large picture hangs over the beds.\n"
);
add_prop(ROOM_I_INSIDE, 1);
add_exit("/d/Terel/mecien/mountains/house2","west",0);
add_item(({"painting","picture"}),
"It is of a giant woman with red eyes.\n"
);
add_item(({"hole","toilet"}),
"YUCK! It must be a where the residents relieve themselves.\n"
);

reset_room();
}
