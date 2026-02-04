/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>

#define PATH "/d/Terel/mecien/valley/guild/courtyard/"
#define TP this_player()

int many;

reset_room(arg){
   many = 5;
   
}

create_room(){
   
   set_short("Rose Garden");
   set_long(
      "Amidst the hedges of evergreen, this small circle in the garden\n"
      +"contains a large patch of roses. Growing upwards on a tall trellis\n"
      +"of redwood, they blossum in full colour.\n"
      +"A simple stone path leads northeast through the hedges, to the\n"
      +"southwest is a small building.\n"
   );
   
   add_item("roses", "They are of many colours and varieties, all are\n"
      + "quite beautiful.\n");
   add_item("trellis", "A latticework frame, made of redwood, on which\n"
      + "the roses grow.\n");
   add_item("hedges", "They are evergreens.\n");
   add_item("evergreens", "They are of many varieties, forming tall hedges.\n");
   add_item("path", "A simple path of white stones.\n");
   add_item("patch", "It is a large growth of roses.\n");
   add_item("building", "It appears to be a shed, it has a thatched roof.\n");
   add_cmd_item("rose", "pick", "@@roses");
   
   add_exit(PATH + "g3", "northeast", 0);
   add_exit(PATH + "sh1", "southwest", 0);
   
   reset_room();
   
}

roses(){
   object obj;
   many --;
   
   if(many < 1){
      write("No more may be picked at this time.\n");
      return 1;
   }
   
   if(this_player()->query_guild_name_occ()!="The Ancient Mystic Order"){
      write("You only manage to prick your fingers on the thorns of the roses.\n");
      say(QCTNAME(this_player()) + " tries to pick a rose.\n");
      return 1;
   }
   
   write("You pick a roses from the patch.\n");
   say(QCTNAME(this_player()) + " picks a rose from the patch.\n");
   obj = clone_object("/d/Terel/mecien/valley/guild/obj/rose");
    obj->move(TP);
   
   return 1;
   
}


