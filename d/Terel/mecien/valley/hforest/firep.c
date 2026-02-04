inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>

#define PATH "/d/Terel/mecien/valley/hforest/"

#define TO this_object()
#define EN environment
#define TP this_player()


object mon;

reset_room(){
   
   if(mon) return 0;
   mon=clone_object("/d/Terel/mecien/mountains/ogre");
   mon->set_agressive(1);
   mon->set_random_move(1);
   mon->move(TO);
   
}

create_room(){
   
   set_long("Dark Forest");
   set_long(
      "A darkened forest, filled with trees that seem altogether shadowy "
      +"and somehow unpleasant, as if they had some spirit of evil dwelling within them. " +
      "It is cold here, a wind blowing with bits of ice." +
      " A massive fire pit is dug in the ground here, all about it " +
      "is a ring of stones." +
      "\n");
   
   add_item("trees", "These dark forboding trees haunt this place, like sentinals of some great evil.\n");
   add_item("stones", "They are crude stones taken from the river.\n");
   add_item(({"fire pit", "fire", "pit"}), "It is deep and filled " +
      "with horrible ash and debris.\n");
   add_cmd_item("pit", "enter", "@@go_pit");
   add_item("ash", "It is in the pit.\n");
   add_item("debris", "Looks to be bones and logs in the pit.\n");
   
   
   add_exit(PATH + "df1", "southwest", 0);
   add_exit(PATH + "df2", "north", 0);
   
   
   add_exit(PATH + "df3", "east", 0);
   
   add_prop(CONT_I_LIGHT, 0);
   reset_room();
   
}

go_pit(){
   TP->move_living("down into the pit", PATH + "pit_bot");
   tell_room(EN(TO), "A horrible noise is heard from the pit.\n");
  return 1;
}

