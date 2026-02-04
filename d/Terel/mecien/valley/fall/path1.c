inherit "std/room";

create_room(){

  set_short("Forest Path");
  set_long("A light path runs east-west through the forest here. Trees\n" +
          "in the midst of their fall hang over the path, coloring this\n" +
          "trail with many leaves. Very little light escapes through\n" +
          "the canopy down to the path.\n");
   add_exit("/d/Terel/mecien/valley/path7", "west", 0);
   add_exit("/d/Terel/mecien/valley/fall/path2", "east", 0);

}

