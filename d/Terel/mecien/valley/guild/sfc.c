/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>

#define PATH "/d/Terel/mecien/valley/guild/"

reset_room(arg){

object obj;

if(present("teacher")) return 0;
obj=clone_object(PATH + "ft");
obj->move(this_object());

}

create_room(){

set_short("Sacred Fire Chamber");
set_long(
"Dark and mysterious, this small oval shaped chamber is lit only by the\n"
+"flickering flame from the sacred fire housed in the hearth. The walls\n"
+"and ceiling here are layered in a gold colour tile, each brilliant and\n"
+"sparkling in the reflection of the light. A great stone urn rests in the\n"
+"center of the chamber, alone.\n"
);

add_item("hearth", "It is to the north.\n");
add_item(({"flame", "fire"}), "It resides within the hearth to the north,\n"
   + "illuminating this chamber with its hallowed glow.\n");
add_item("tile", "Small tiles of gold that coat the ceiling and walls of this\n"
  +"small chamber, each of hexagon shape.\n");
add_item("ceiling", "It is oval, coated in gold tiles.\n");
add_item("urn", "It is a massive an arcane looking stone urn. It seems\n"
  + "cold and lifeless. There is an inscription that circles its\n"
  + "outer rim.\n");
add_cmd_item(({"urn", "inscription", "writing"}), "read", "@@read");

add_exit(PATH + "hearth", "north", 0);

reset_room();

}


read(){

if(this_player()->query_skill(SS_LANGUAGE) < 30){

write("It is too obscure to read.\n");
return 1;
}

write("LET THIS FIRE LEAD YOUR WAY TO TRUTH\n");
write(" FOR TRUTH ABIDES WITHIN IT ALWAYS\n");
return 1;

}




