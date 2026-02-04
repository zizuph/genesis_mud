inherit "/std/room";

#define TO this_object()
#define PATH "/d/Terel/mecien/valley/hforest/"

object mon;

reset_room(){
  if(mon) return 0;
  mon=clone_object(PATH + "skeleton");
   mon->move(TO);
}

create_room(){
  set_short("River's Edge");
  set_long(
  "The small river that winds through the forest, passes through here, " +
"widening as it heads south. It is almost frozen here. Trees loom up to " +
"the north and east.\n"
);

add_item("trees", "They are icy, cold and seem lifeless.\n");
add_item("river", "It is icy.\n");
add_item("ice", "It is a thin layer of ice on the river.\n");

add_exit(PATH + "pine1", "northeast", 0);

reset_room();

}

