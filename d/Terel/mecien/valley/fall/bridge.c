inherit "/std/room";

#define PATH "/d/Terel/mecien/valley/"

object mon;

reset_room(arg){
if(mon) return 0;
      mon=clone_object(PATH + "fall/wm");
      mon->move(this_object());
}

create_room(){
   set_short("Old Covered Bridge");
   set_long(
      "This is an old covered wooden bridge. It was finely crafted long\n"
      +"but seems to be rather worn and decayed. It spans a swift and icy\n"
      +"river that flows to the south.\n"
   );
   
   add_exit(PATH + "fall/path3", "west", 0);
   add_exit(PATH + "hforest/edge", "east", 0);
   
   add_item("river", "It looks rather deep, swift and cold.\n");
   add_item("bridge", "It is stable.\n");
   
   reset_room();
}

