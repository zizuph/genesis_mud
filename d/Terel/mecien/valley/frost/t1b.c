inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Terel/mecien/valley/frost/local.h"

create_room(){

set_short("Ice Fortress Tower");
set_long(break_string(
"A massive icy tower hall, filled with furs and bedding. From here one " +
"can see out over the valley and look upon the gates. A huge wooden rack " +
"rests against the wall. A huge set of " +
"steps leads down. A flap of fur, covers the exit to the walls." +
"\n", 70));
add_item("flap", "It leads out onto the wall, it keeps the wind out.\n");
add_item("gates", "@@gates");
add_item("steps", "They are icy stone.\n");
add_item("furs", "They are nasty and filthy, of deer and ram.\n");
add_item("bedding", "Massive wooden frames filled with furs.\n");
add_item("ice", "It covers the walls and ceiling.\n");
add_item("ceiling", "Made of huge stone blocks, now coated with ice.\n");
add_item("floor", "Slick with ice.\n");
add_item("walls", "Huge stone blocks, coated with ice.\n");

INSIDE;

add_exit(PATH + "t1a", "down", "@@check");


}

gates(){
  
  write("The gates are huge!");
  return 1;
  
}


check(){
  if((TP->query_stat(SS_DEX) + random(100)) < 100){
   write("You slip on the steps.\n");
   TP->add_attack_delay(12);
   say(QCTNAME(TP) + " slips on the steps and falls.\n");
   return 1;
 }

}


