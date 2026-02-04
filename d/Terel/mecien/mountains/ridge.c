inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>

reset_room(arg){

object chisel;
if(present("chisel")) return;
chisel=clone_object("/d/Terel/mecien/mountains/chisel");
chisel->move(this_object());

}

create_room(){
set_short("Ridge");
set_long(
"This small ridge leads around the mountains. North is the main chain\n"
+"of ice mountains. There is a small vale to the south.\n"
+"There are scratchings on the cliff walls.\n");
add_item("scratchings", "They may once have been words, but are faded now.\n");
add_exit("/d/Terel/mecien/mountains/gap","north", 0);
add_exit("/d/Terel/mecien/mountains/vale","south",0);

reset_room();
}

