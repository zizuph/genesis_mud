inherit "std/room";

create_room(){

  set_short("Forest Path");
  set_long("A light path runs east-west through the forest here. Trees\n" +
          "in the midst of their fall hang over the path, coloring this\n" +
          "trail with many leaves. Very little light escapes through\n" +
          "the canopy down to the path.\n");
   add_item("trees", "All the trees are in the autumn stage. Beautiful with\n"
+ "brilliant colours.\n");
add_item("path", "It is a simple dirt path running east-west.\n");
   add_exit("/d/Terel/mecien/valley/fall/path1", "west", 0);
   add_exit("/d/Terel/mecien/valley/fall/path3", "east", 0);
   add_exit("/d/Terel/mecien/valley/fall/forest2", "northwest", 0);

}

blocked(){

write("The path has been blocked by fallen trees.\n");
return 1;
}


