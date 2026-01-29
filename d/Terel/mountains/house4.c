

inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>

reset_room(){

object giant;
if(present("giant")) return;
giant=clone_object("/d/Terel/mountains/obj/giant");
giant->move(this_object());

}

create_room(){
set_short("Chamber");
set_long(
"This chamber is filled with a large bed, full of stinking rags and\n"
+"unclean furs. The floor is slicked by grease and other foods stains.\n"
+"A set of stairs leads down to what seems a cellar.\n");
add_prop(ROOM_I_INSIDE, 1);
 add_exit("/d/Terel/mountains/house2","south","@@guarded2");
 add_exit("/d/Terel/mountains/cellar1","down","@@guarded",1);
add_item(({"cellar","stairs"}),
"It looks dark down there.\n");
reset_room();
}

int guarded(){
 object giant;
 giant=present("giant");
 if(this_player()!=this_interactive()) return 0;
 if(giant && giant->query_name()!="corpse"){
  write("The giant pushes you back.\n");
  say("The giant pushes "+QCNAME(this_player())+" against the wall.\n");
  return 1;
 }
 return 0;
}

int guarded2(){
 object giant;
 giant=present("giant");
  if(this_player()!=this_interactive()) return 0;
 if(giant && giant->query_name()!="corpse"){
  if(random(2)){
   write("The giant attempts to stop you from leaving, but you get away.\n");
   say("The giant attempts to stop "+QCNAME(this_player())+" from leaving, "
   +"but fails.\n");
   return 0;
  }
  write("The giant pushed you back.\n");
  say("The giant pushes "+QCNAME(this_player())+" against the wall.\n");
  return 1;
 }
 return 0;
}
