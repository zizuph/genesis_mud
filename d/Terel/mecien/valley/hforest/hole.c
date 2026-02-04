inherit "/std/room";

#define PATH "/d/Terel/mecien/valley/hforest/"

object mon;

reset_room(arg){
if(mon) return 0;
mon=clone_object(PATH + "wyvern");
mon->move(this_object());
}

create_room(){
set_short("Dead Oak");
set_long(
"This is the inner parts of a dead oak tree. It has been carved\n"
+"out by some large creature. The floor is covered with bits of\n"
+"pines and other plants, animal bones and unidentifiable things.\n"
);

add_exit(PATH + "forest6", "out", 0);
add_item("pines", "Bits of pines that have been torn down.\n");
add_item("bones", "They look to be those of humans and perhaps bears.\n");


reset_room();
}
