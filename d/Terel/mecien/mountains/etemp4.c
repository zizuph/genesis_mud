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
      "This part of the building is all but passed away. Nothing seems " +
      "to remain, excepting the walls and ceiling.\n"
      +"Much of the walls and ceiling have collapsed into piles of rubble.\n"
   );
   
  add_item("hole", "It might have been a stairway at one time.\n");
  add_cmd_item("hole", "enter", "@@go_hole");
   add_item("walls", "They are crumbling and ruinous, though they remain.\n");
   add_item("ceiling", "Mostly crumbled away, but still providing some shelter.\n");
   add_item("glassy stone", "It is black, most probably volcanic.\n");
   add_item("rubble", "It is piled all about the room, formed from the collapse of the ceiling and walls. " + 
      "One pile of rubble seems to cover a hole.\n");
   
   add_exit(PATH + "etemp2", "west", 0);
}

go_hole(){
  TP->move_living("X", PATH + "etemp5");
   tell_room(TO, QCTNAME(TP) + " searches through the rubble.\n");
 return 1;
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

