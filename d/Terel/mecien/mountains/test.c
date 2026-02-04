inherit "/std/room";
#include <stdproperties.h>


reset_room(){
 int n;

 if(!present("goblin")) {
     n= 10;
     call_out("goblins", 1, n);
     }
}

goblins(n) {
  object ob;
  ob=clone_object("/d/Terel/mecien/mountains/goblin");
/*
  ob->move(this_object());
*/
  ob->move_living("xx", this_object());
  n--;
  if (n > 0) 
    call_out("goblins", 0, n);
 
}

create_room(){
set_short("Quarters");
set_long(
"This small hall seems to be the living quarters of the\n"
+"of the residents. The stench here is unbearable. Mats of\n"
+"fur and cloth line the floor as bedding.\n"
);
add_prop(ROOM_I_INSIDE, 1);
add_exit("/d/Terel/mecien/mountains/ghall","west",0);
reset_room();
}
