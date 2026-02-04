inherit "/std/room";

#define PATH "/d/Terel/mecien/valley/sf/"

object mon;

reset_room(arg){
   if(mon) return 0;
   mon=clone_object("/d/Terel/mecien/valley/ggiant");
   mon->move(this_object());
}

create_room(){
   set_short("Forest Edge");
   set_long(
      "A great forest, in the midst of spring rises up here and spreads\n"
      +"out to the north and east. It is filled with beautiful trees, many\n"
      +"of which are now in bloom.\n"
   );
   
   add_item("trees", "There are multitudes, mostly deciduous, but also a few\n"
      +"evergreens mixed in.\n");
   
   add_exit(PATH + "f2", "north", 0);
   add_exit("/d/Terel/mecien/valley/elanding", "southwest", 0);
   
   reset_room();
}
