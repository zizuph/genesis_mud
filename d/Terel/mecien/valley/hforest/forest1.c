inherit "/std/room";
#include <stdproperties.h>

object ob;


reset_room(){
   int n;
   
   if(!present("skeleton")) {
      n= 6;
      call_out("skeletons", 1, n);
   }
}

skeletons(n) {
  if(ob) return 0;
   ob=clone_object("/d/Terel/mecien/valley/hforest/skeleton");
   /*
   ob->move(this_object());
   */
   ob->move_living("xx", this_object());
   n--;
   if (n > 0) 
      call_out("skeletons", 0, n);
   
}

create_room(){
   set_short("Haunted Forest");
   set_long(
      "This is the depths of a cold and dismal forest. Almost everything\n"
      +"here is either dead or dying. The trees are black and lifeless.\n"
      +"The crumbled remains of a wall stands here.\n"
   );
   add_item(({"wall","remains","ruins"}),
      "It looks like a tower once stood here.\n");
   
   add_prop(ROOM_I_LIGHT, -1);
   add_exit("/d/Terel/mecien/valley/hforest/mound", "north", 0);
   add_exit("/d/Terel/mecien/valley/hforest/forest5","west",0);
   reset_room();
}
