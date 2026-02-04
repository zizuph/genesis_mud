inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>

#define PATH "/d/Terel/mecien/valley/hforest/"

#define TO this_object()

object mon;


create_room(){
   
   set_long("Dark Forest");
   set_long(
      "A darkened forest, filled with trees that seem altogether shadowy "
      +"and somehow unpleasant, as if they had some spirit of evil dwelling within them. " +
      "It is cold here, a wind blowing with bits of ice." +
      "Most of the trees here are broken here, seemingly smashed " +
      "or cut for firewood. Some of the broken trees reveal a cave " +
      "to the northwest that is very large." +
      "\n");
   
   add_item("trees", "These dark forboding trees haunt this place, like sentinals of some great evil.\n");
   
   
   add_exit(PATH + "df2", "southeast", 0);
/*
   add_exit(PATH + "ecave1", "northwest", 0);
*/
   
   add_prop(CONT_I_LIGHT, 0);
   
}

