inherit "std/room";
#define PATH "/d/Terel/mecien/valley/city/"

reset_room(arg){
   object potter;
   if(present("potter")) return;
   potter=clone_object(PATH + "potter");
   potter->move(this_object());
   return 1;
}

create_room(){
   
   set_short("Pottery Shop");
  set_long(
  "This small stone room is dimly lit, its wall and ceiling of a coarse\n"
+ "and craggy rock. The walls are covered with oak shelves, displaying\n"
+ "different types of earthenware. A circular rug of dull red covers\n"
+ "the main floor area.\n"
);
   
  add_item("earthenware", "Many varities of potterry and such, only for display.\n");
  add_item("ceiling", "It is made from coarse and craggy rock.\n");

  add_item("shelves", "They are oak and cover the walls.\n");
  add_item("rug", "It is a dull red rug, circular and covers most of the room.\n");
   add_exit(PATH + "street1", "west", 0);
   
   reset_room();
}




