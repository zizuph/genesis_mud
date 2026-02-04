inherit "/std/room";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Terel/mecien/valley/frost/local.h"

create_room(){

  object door;

set_short("Ice Fortress Tower");
set_long(break_string(
"A massive icy tower hall, filled with furs and bedding. It seems this " +
"is a bunking place for guards. A large pit is in the center of the hall, " +
"filled with ash and bones. A huge stone, stained with blood rests next to " +
"the pit. A huge set of steps leads up." +
"\n", 70));
add_item("pit", "It is a fire pit, used for cooking. Filled with ash and bone.\n");
add_item("bones", "They look to be dwarf bones.\n");
add_item("ash", "Remains of the fire.\n");
add_item("stone", "It looks like it is used for cutting meat and bashing skulls upon.\n"); 
add_item("steps", "They are icy stone.\n");
add_item("furs", "They are nasty and filthy, of deer and ram.\n");
add_item("bedding", "Massive wooden frames filled with furs.\n");
add_item("ice", "It covers the walls and ceiling.\n");
add_item("ceiling", "Made of huge stone blocks, now coated with ice.\n");
add_item("floor", "Slick with ice.\n");
add_item("walls", "Huge stone blocks, coated with ice.\n");

INSIDE;

add_exit(PATH + "t2b", "up", "@@check");

door = clone_object(PATH + "d2b");
door->move(TO);

}


check(){
  if((TP->query_stat(SS_DEX) + random(100)) < 100){
   write("You slip on the steps.\n");
   TP->add_attack_delay(12);
   say(QCTNAME(TP) + " slips on the steps and falls.\n");
   return 1;
 }

}


