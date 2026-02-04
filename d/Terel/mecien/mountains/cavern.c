inherit "/std/room";
#include <stdproperties.h>

#define PATH "/d/Terel/mecien/mountains/"

reset_room(){
 int n;
 if(!present("goblin")) {
     n = 8;
     call_out("goblins", 1, n);
     }
}

goblins(n) {
  object ob;
  ob=clone_object("/d/Terel/mecien/mountains/goblin");
  ob->move_living("X", this_object());
  n--;
  if (n > 0)
   call_out("goblins", 0, n);

}

create_room(){
set_short("Cavern");
set_long(
"This massive cavern has been carved from stone and ice, the work\n"
+"of bad quality. A smell of salt, dung and smoke fills the cavern\n"
+"making it almost unbearable. Refuse is piled everywhere.\n"
);
add_exit(PATH + "t1", "east", 0);
add_prop(ROOM_I_INSIDE, 1);
add_exit("/d/Terel/mecien/mountains/pass","north",0);
add_exit("/d/Terel/mecien/mountains/ghall","south",0);
reset_room();
}
