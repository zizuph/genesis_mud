inherit "std/room";

create_room(){

  set_short("Forest Path");
  set_long("A light path runs east-west through the forest here. Trees\n" +
          "in the midst of their fall hang over the path, coloring this\n" +
          "trail with many leaves. Very little light escapes through\n" +
  "the canopy down to the path.\n"
 +"A huge covered wooden bridge spans across a swift and somewhat\n"
+"icy river here. The forest on the east side of the river is full\n"
+"of dark pines that are coated with snow and ice.\n"
);
   add_item("trees", "All the trees are in the autumn stage. Beautiful with\n"
+ "brilliant colours.\n");
  add_item("river", "It is a swift and icy river, cutting the forest\n"
  +"into sections, the war side seeming to be much colder.\n");
  add_item("bridge", "It is a huge covered wooden bridge. It looks in fair shape.\n");
add_item("path", "It is a simple dirt path running east-west.\n");
   add_exit("/d/Terel/mecien/valley/fall/path2", "west", 0);
   add_exit("/d/Terel/mecien/valley/fall/bridge", "east", 0);

}

blocked(){

write("The path has been blocked by fallen trees.\n");
return 1;
}


