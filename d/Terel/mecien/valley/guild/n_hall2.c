/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>

#define PATH "/d/Terel/mecien/valley/guild/"

init(){
add_action("place", "place");
::init();
}

place(string str){
if(!str) return 0;
if(str == "my right hand upon the disk"){
write("You place your hand upon the disk.\n");
write("A secret chambers opens and you are moved within.\n");
this_player()->move_living("this place", PATH + "ss1");

return 1;
}
return 0;
}

create_room(){

set_short("Hallway");
set_long("A dark stone hallway, its unusual stonework is a\n"
  +"layered work of flate scale-like peices of slate. They are\n"
  +"atop each other like bricks. It is of ancient days, a bit\n"
  +"worn, but still strong. A silver disk is set into the west\n"
   +"wall, it shines bright.\n");

add_item("disk", "It is a circular disk of silver. It shines bright\n"
  + "and casts a strange glow.\n");
add_exit(PATH + "n_hall3", "north", 0);
add_exit(PATH + "n_hall1", "south", 0);


}
