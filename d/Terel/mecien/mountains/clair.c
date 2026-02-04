inherit "/std/room";

object monster;

reset_room(arg){
if(!monster){
monster = clone_object("/d/Terel/mecien/mountains/bcen");
monster->move(this_object());
}
}

create_room(){
set_short("Snow Cave");
set_long(
"This a large cave that has been burrowed out of the snow. " +
"The ground is littered with feces and bones.\n");

add_item("feces", "It is what it is! Pew!\n");
add_item("bones", "They are the remains of something that fed here.\n");

add_exit("/d/Terel/mecien/mountains/ice14", "up", 0);
reset_room();
}
