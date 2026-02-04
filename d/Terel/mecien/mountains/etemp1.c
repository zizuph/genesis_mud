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
"Charnel and abyssmal, this place hearkens from the most desolate "
+ "and despairing reaches of darkness. The ruins of some ancient "
+ "temple arise here from a massive foundation of black, glassy "
+ "stone. The walls and ceiling mostly crumbled away, but standing as "
+ " a haunting remnant of its former days. Though the mountains drape this "
+ "place in the shadows of their midst, it stands out, crying aloud " 
+ "some shameful woe of the past. A twisted path leads up the mountainside to "
+ "a darkened cliff.\n"
);
add_item("mountains", "The surround this dark place.\n");
add_item("walls", "They are crumbling and ruinous, though they remain.\n");
add_item("path", "It twists up the mountainside to a cliff.\n");
add_item("ceiling", "Mostly crumbled away, but still providing some shelter.\n");
add_item("glassy stone", "It is black, most probably volcanic.\n");
add_item("ruins", "They are the ruins of some dark temple.\n");
add_item("temple", "It is a dark ruinous temple, resting upon a great foundation " +
"of black glassy stone.\n");
add_item("It is the base upon which the temple is built, some strange black, "
+ " glassy stone.\n");

add_exit(PATH + "dcliff", "up", 0);
add_exit(PATH + "etemp2", "enter", "@@darkness");
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

