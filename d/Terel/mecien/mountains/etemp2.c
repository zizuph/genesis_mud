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
"This seems to once have been the foyer of this dark place, now cast almost " +
"in total ruin. The celing, though cracked and broken, still provides cover. " +
"The floor is made of some glassy stone. Many broken and aged statues " +
"line the walls here, interspersed with iron sconces.\n"
);

add_item("sconces", "They are black iron, made to hold large candles.\n");
add_item("statues", "Made of stone, they take the shapes of hideous " +
"demonic creatures. Now broken and worn away.\n");
add_item("walls", "They are crumbling and ruinous, though they remain.\n");
add_item("ceiling", "Mostly crumbled away, but still providing some shelter.\n");
add_item("glassy stone", "It is black, most probably volcanic.\n");
add_item("block", "It is the base upon which the temple is built, some strange black, "
 + " glassy stone.\n");

add_exit(PATH + "etemp3", "north", 0);
add_exit(PATH + "etemp1", "out", "@@darkness");
add_exit(PATH + "etemp4", "east", 0);
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

