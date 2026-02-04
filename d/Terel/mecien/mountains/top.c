inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>

reset_room(arg){

object baltar;
if(present("altar")) return;
baltar=clone_object("/d/Terel/mecien/mountains/baltar");
baltar->move(this_object());

}

create_room(){
set_short("Mountain Top");
set_long(
"This is the mountains top. Ridges of black stone rise out of\n"
+"the earth. The clouds above flash lightning. In the center of\n"
+"this place is a black stone dias. Around it are nine stones\n"
+"that form a ring.\n");
add_item(({"sky", "clouds", "weather"}),
  "It is a black and twisted sky, full of shadowy clouds and\n"
  + "bursts of eratic lightning.\n");
add_item("stones",
 "Nine circular stones set into the ground about the dias.\n");
add_item("dias", "It is a circular black stone platform, very low,\n"
+"as if it is meant to have something set upon it.\n");
add_exit("/d/Terel/mecien/mountains/dcliff","down", 0);

reset_room();
}

