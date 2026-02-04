/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

#define PATH "/d/Terel/mecien/valley/guild/courtyard/"
#define TP   this_player()
#define TO   this_object()

int nm;
reset_room(arg){
   nm = nm + 1;
}

init(){
   add_action("sing", "sing");
   ::init();
}

sing(str){
   
   if(!str) return 0;
   if(str == "to the glory of the Ancients"){
      write("Someone cries: If ye be to their glory, enter in!\n");
      say(QCTNAME(TP) + " sings a song of glory!\n");
      TP->move_living("into a mysterious opening in the hill!", PATH + "fh");
      return 1;
   }
}


create_room(){
   
   set_short("Forest Hill");
   set_long(
      "Amidst the enchanted forest of deep redwoods and cedars, this\n"
      +"ancient hill rises. Older than the forest itself, set atop the\n"
      +"hill are ruins of some stone structure. A thick moss of lurid\n"
      +"green grows over everything, sprouting tiny blue-gray flowers, as\n"
      +"do the many bright white mushrooms.\n"
   );
   
   nm = 5;
   add_cmd_item("mushroom", "pick", "@@mushroom");
   add_item(({"ruins", "ruin", "structure"}),
      "It is too ancient and the stone too crumbled to tell anything of\n"
      + "what it once was.\n");
   add_item("mushrooms", "The are small, covering the hill with their bright\n"
      +"white shapes.\n");
   add_item("flowers", "They are blue-gray and stem from the moss.\n");
   add_item("moss", "It is a lurid green. The moss itself covers most\n"
      + "everything, and blankets out over the forest floor.\n");
   add_item("trees", "They are mostly redwoods and cedars.\n");
   add_item("redwoods", "Tall stately trees.\n");
   add_item("cedars", "Glorious coniferous trees.\n");
   
   add_exit(PATH + "mf1", "southeast", 0);
   reset_room();
}

mushroom(){

object obj;

   if (nm >= 1) {
    nm--;
      write("You pick a mushroom from the hillside.\n");
say(QCTNAME(this_player()) + " picks a mushroom from the hillside.\n");
  seteuid(getuid(this_object()));
  obj = clone_object("/d/Terel/mecien/valley/guild/obj/herb2");
  obj->move(this_player());
      return 1;
   }
write("The mushrooms are too small.\n");
return 1;
}
   
   
