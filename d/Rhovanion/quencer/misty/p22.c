/* highpass */

inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h"
#include "/sys/stdproperties.h"
#include <macros.h>

create_room()
{
    add_prop(ROOM_I_INSIDE, 0);
    set_short("by the river");
    set_long("This is the end of the grassy path. It can't go any further "+
             "east because it is blocked by swift currents of River Anduin. "+
             "It seems that all your hopes to escape this way were wrong. "+
             "You must turn back and seek some other way.\n");

    add_item("path", "It comes from the west direction but here it stops. "+
                     "Maybe it is used only by goblins when they want to "+
                     "have fish for lunch.\n");
    add_item(({"river","water"}), "The water is icy cold and runs swiftly to "+
                                  "the south.\n");

              /* The other room,           direction, VBFC, fatigue */
    add_exit(MISTY_DIR+"p21", "west",    0,    4);

}

init()
{
    ::init();
    add_action("enter_river", "enter");
}

int
enter_river(string river) {
  if(river != "river")
  {
    NF("Enter what?\n");
    return 0;
  }
  TP->catch_msg("You decided that there is nothing as bad as going "+
                "back to those goblin caves and not caring about your "+
                "life you jump into the water.\n");
  say(QCTNAME(TP)+" decided that there is nothing as bad as going "+
                "back to those goblin caves and not caring about "+
                TP->query_possessive()+" life "+TP->query_pronoun()+
                " jumps into the water.\n");
  TP->move_living("M",MISTY_DIR+"river");
  call_out("in_river_1",4);
  return 1;
}
void in_river_1(){
  TP->catch_msg("Ooops!!! This wasn't so good an idea. Now you will drown "+
                "for sure.\n");
  call_out("in_river_2",4);
}
void in_river_2(){
  TP->catch_msg("No! Not yet! Maybe this branch hanging over the water "+
                "can save your life.\n");
  call_out("in_river_3",4);
}
void in_river_3(){
  TP->catch_msg("Damn! You are too exhausted to climb on it... The river "+
                "grabs you again and your fight for life continues.\n");
  call_out("in_river_4",4);
}
void in_river_4(){
  TP->catch_msg("Ouch! There were some rock under the water surface. "+
                "Maybe the water becomes shallower here?\n");
  call_out("in_river_5",4);
}
void in_river_5(){
  TP->catch_msg("Yes! You can stand up here! You are saved! Now hurry out "+
                "of the water so you don't slip back in again.\n");
  call_out("in_river_6",4);
}
void in_river_6(){
  TP->catch_msg("You crawl out of the river choking on the water.\n");
    TP->move_living("M",ANDUIN_DIR + "oldpath3");
  tell_room(ANDUIN_DIR+"oldpath3", QCTNAME(TP)+" crawls out of the river "+
                             "choking on the water.\n", TP);
}
