inherit "std/room";
#define PATH "/d/Terel/mecien/valley/city/"

reset_room(arg){
   object tailor;
   if(present("tailor")) return;
   tailor=clone_object(PATH + "tailor");
   tailor->move(this_object());
   return 1;
}

create_room(){
   
   set_short("Clothing Shop");
    set_long(
  "This simple and modest little shop is filled with tapestries and bolts\n"
  +"of cloth. Small racks line the walls, in which articles of clothing are\n"
   +"stored, upon the floor is a large woven rug. The smell of cedar\n"
   +"fills this place, no doubt to the wood of its construction.\n"
);
   add_item("racks", "The are tall, made of cedar wood and hold clothing.\n");
   add_item("tapestries", "They are simple and line the walls.\n");
    add_item("bolts", "They are large bolts of fabric.\n");
   add_item("fabric", "It is wool, silk and cotton used to make clothes.\n");
  add_item("rug", "It covers the floor of the shop, it is neatly woven and\n"
   + "and contains the pattern of a ram.\n");
  add_item("wood", "It is cedar.\n");
   add_exit(PATH + "street1", "east", 0);
   
   reset_room();
}




