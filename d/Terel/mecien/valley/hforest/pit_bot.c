inherit "/std/room";
#include <stdproperties.h>

#define TO this_object()
#define TP this_player()
#define EN environment
#define PATH "/d/Terel/mecien/valley/hforest/"

object mon;
int something = 3;

reset_room(){
  if(mon) return 0;
   mon =clone_object("/d/Terel/mecien/valley/sf/dc");
   mon->move(TO);
}



create_room(){
   
   set_short("Bottom of Fire Pit");
   set_long(
      "Filled with horrible ash and soot, this is the bottom of a " +
      "large fire pit. Burned logs, bones and pieces of wood are strewn " +
      "about all over.\n"
   );
   
   add_prop(OBJ_S_SEARCH_FUN, "@@search_ash");
   add_prop(OBJ_I_SEARCH_TIME, 10);
   
   add_item("ashes", "Tons of it, from countless fires burned here.\n");
   add_item("logs", "they are mostly burned away.\n");
   add_item("wood", "Pieces of wood that have been burned.\n");
   add_item("bones", "Fragments of bones thrown into the fire. They look chewed.\n");
   
   
   add_exit(PATH + "firep", "up", 0);
   
   reset_room();
   
}

search_ash(){
   int n;
   object ob;
   if(something){
      ob = clone_object("/std/corpse");
  ob->set_name("wasil");
   ob->set_short("decaying corpse of an elf");
  ob->set_long("It is a decaying corpse of an elf, burned by fire.\n");
      ob->move(TO);
      write("You find a corpse amidst the ashes.\n");
      TP->command("scream");
   return 1;
   }
}

