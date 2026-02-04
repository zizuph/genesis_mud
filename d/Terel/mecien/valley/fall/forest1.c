inherit "/std/room";

create_room(){

  set_short("Forest of Fall");
  set_long("A deep forest, colored by aged elms, oaks, fir, pine\n" 
         + "maple, hickory and birch trees. The whole forest stands\n"
         + "in the midst of fall, the ground covered with brightly\n"
         + "colored leaves.\n");
  add_exit("/d/Terel/mecien/valley/fall/forest3", "northeast", 0);
  add_exit("/d/Terel/mecien/valley/path6", "west", 0);

}


