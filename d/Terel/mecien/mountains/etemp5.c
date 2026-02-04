inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>

#define TP this_player()
#define TO this_object()
#define ENV environment
#define PATH "/d/Terel/mecien/mountains/"

create_room(){
   
   set_short("Ruined Temple");
   set_long(
      "This place seems to have been destroyed by a fire. The walls " +
      "and ceiling made form the same glassy rock, yet scratched and " +
      "imbedded with ash and burn marks. A rough hewn passage leads down.\n");
   
  add_prop(ROOM_I_LIGHT, -1);
   add_item("ash", "It seems to have been here for a very long time, " +
      "perhaps the remains of a fire.\n");
   add_item("marks", "They look like they were created by some monster.\n");
   add_item("glassy stone", "It is black, most probably volcanic.\n");
   
   add_exit(PATH + "etemp4", "up", 0);
   add_exit(PATH + "dpas1", "down", 0);
}




darkness(){
   object target;
   if(random(2)){
      target = TP;
      set_alarm(5.0, -1.0, "add_tick", target);
   }
}

add_tick(object target){
   object tick;
   
   tick = clone_object(PATH + "tick");
   tick->change_prop(OBJ_M_NO_GET, 0);
   tick->move(target);
   tick->change_prop(OBJ_M_NO_GET, 1);
   tick->change_prop(OBJ_M_NO_DROP, "It is stuck to you!\n");
}

