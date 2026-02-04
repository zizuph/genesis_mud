inherit "std/room";
#define PATH "/d/Terel/mecien/valley/city/"

reset_room(arg){
   object quilter;
  if(quilter) return;
   quilter=clone_object(PATH + "quilter");
   quilter->move(this_object());
   return 1;
}

create_room(){
   
   set_short("Quilt Shop");
   set_long(
      "This small warm shop, is covered with wood panels. Some of the walls " +
      "are lined with quilting work. A wood shelf stands in back.\n"
   );
   
   add_item("panels", "They are fine wood and make this place very pleasant.\n");
   add_item(({"quilting work", "work", "quilts", "quilting"}), "Fine quilts and bits of needlework.\n");
   add_item("supplies", "Common quilting materials.\n");
   add_item("shelf", "It is filled with quilting supplies.\n");
   add_exit(PATH + "street11", "north", 0);
   
   reset_room();
}




