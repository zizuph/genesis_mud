/* This is the room containing the Pirates Bulletin board     */

inherit "/std/room";
#include "defs.h"

void
create_room()
{
   object board;
   
   set_short("Pirates Bulletin board room");
   set_long(break_string(
         "This part of the cave is where you should leave messages "+
         "concerning the Pirates. The cave is very warm here. Steam "+
         "rolls in from the exits to the east and west.\n"
         ,74));
   add_item("steam","A light layer of steam rolls in from "+
      "the east and the west.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_exit(THIS_DIR+"main", "up", 0);
   add_exit(THIS_DIR+"train","east","@@is_member");
   add_exit(THIS_DIR+"cave1","west",0);
   
   board=clone_object(THIS_DIR+"pir_board");
   board-> move(this_object());
   
   
   add_item(({"walls","wall"}), break_string(
         "The walls are warm and damp to the touch. The heat seems to "+
         "be eminating from two of the exits here.\n"
         ,74));
   add_item(({"floor","ground"}),break_string(
         "The floor is covered in a light layer of steam. "+
         "It is rather warm.\n"
         ,74));
   
}

int
is_member()
{
   if(TP->query_guild_name_occ() != GUILD_NAME)
      return 0;
   write("Sorry, only pirates are allowed in the training room.\n");
   return 1;
}
