inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>

#define NUM 2
#define TP this_player()


reset_room(arg){
   object *cwraith;
   int i;
   cwraith=allocate(NUM);
   if(present("wraith")) return;
   for(i=0; i<NUM; i++){
      cwraith[i]=clone_object("/d/Terel/mecien/valley/hforest/cwraith");
      cwraith[i]->move(this_object());
   }
}

create_room(){
   object bdoor2;
   
   set_short("Barrow");
   set_long(
      "This is the entry chamber of the barrow, it smells of death\n"
      +"and decay. An arch leads north to the center of the barrow.\n"
      +"Bones litter the floor.\n"
   );
   add_prop(ROOM_I_INSIDE, 1);
   
   bdoor2=clone_object("/d/Terel/mecien/valley/hforest/bdoor2");
   bdoor2->move(this_object());
   
  add_item("arch", "It is a black arch that leads north.\n");
   add_exit("/d/Terel/mecien/valley/hforest/barrow2","north","@@wraith");
   add_item(({"bone","bones"}),
      "The bones seem to be those of many humans.\n"
   );
   reset_room();
}

wraith(){
   if(present("wraith")){
      write("The wraith have powers that block the arch.\n");
      say(QCTNAME(TP) + " tries to go north but is stopped by some power.\n");
      return 1;
   }
}

