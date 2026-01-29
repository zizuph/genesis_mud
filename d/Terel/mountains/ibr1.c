

inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>

#define TP this_player()
#define ENV environment
#define MAXWEIGHT 100000

enter_inv(object ob, object from){

int WEIGHT;

if(WEIGHT > MAXWEIGHT){

}

::enter_inv(ob, from);
}

create_room(){

set_short("Ice Bridge");
set_long(
"A great bridge of crystaline ice stretching east and west\n"
+"through the misty mountains. The wind is strong here,\n"
+"making the bridge feel unsafe.\n");

add_item("bridge", "It looks limited in what it can support.\n");
add_item("mist", "It is everywhere.\n");

}

