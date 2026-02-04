inherit "std/room";
#define PATH "/d/Terel/mecien/mountains/"

reset_room(arg){
object ob;
if(!present("ore")){
ob=clone_object("/d/Terel/mecien/valley/guild/quest/ore");
ob->move(this_object());
}
}

create_room(){
set_short("Crater");
set_long(
"Atop this cliff, one can see out across much of the icy mountain\n"
+ "chain and even down to the ravine. There is a large crater here\n"
+ "in the snow and ice.\n"
);

add_item("crater", "It is very large and looks like it was made by a meteor.\n");
add_exit(PATH + "cliff", "down", 0);
reset_room();
}
