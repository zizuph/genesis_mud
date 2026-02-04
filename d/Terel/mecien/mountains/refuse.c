inherit "/std/room";
#include <stdproperties.h>


reset_room(){
 int n;

 if(!present("rat")) {
     n= 6;
     call_out("rats", 1, n);
     }
}

rats(n) {
  object ob;
  ob=clone_object("/d/Terel/mecien/mountains/rat");
/*
  ob->move(this_object());
*/
  ob->move_living("xx", this_object());
  n--;
  if (n > 0) 
    call_out("rats", 0, n);
 
}

create_room(){
set_short("Refuse");
set_long(
"This place seems to be a refuse heap. The floor is littered\n"
+"with bones, rotting food, skins, dung and other things that\n"
+"are not recognizable.\n"
);
add_prop(ROOM_I_INSIDE, 1);
add_exit("/d/Terel/mecien/mountains/guardroom","up",0);
reset_room();
}
