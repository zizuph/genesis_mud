

inherit "/std/room";
#include <stdproperties.h>

#define PATH "/d/Terel/mountains/"

create_room(){
   
   set_short("Tunnel");
   set_long(
      "Crudely carved from the mountains rock, this dark tunnel slopes\n"
  +"downward to the east. A strange hole leads down into darkness. A\n"
  +"strange smell fills the "
  +"cavern, a stench of burning fat.\n");
   
  add_item("hole", "It is a large hole leading into darkness.\n");
   add_exit(PATH + "t3", "east", "@@check");
   
  add_exit(PATH + "t1", "west", 0);
   
   add_prop(ROOM_I_LIGHT, 0);
   add_prop(ROOM_I_INSIDE, 1);
   
}

check(){
write("Something keeps you from entering there.\n");
return 1;
}

init(){
::init();
add_action("enter", "enter");
}

enter(string str){
if(!str) return 0;
if(str == "hole"){
this_player()->move_living("down into the dark hole", PATH + "dh1", 0, 0);
return 1;
}
return 0;
}


