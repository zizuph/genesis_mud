inherit "/std/room";
#include "square.h"

void
reset_room()
{
   object gnome;
   
   gnome = present("gnome");
   if(gnome && gnome->query_name()!="ghost")
      return;
   else
      gnome = clone_object(A_NPC_D + "gnome");
   gnome->move_living(" arrives.", this_object());
}

void
create_room()
{
   
   set_short("Northeast end of square");
   set_long(BSS("You are on the northeastern part of the town square "+
         "in Tyr, just outside the temple. To the southeast you see "+
         "the Temple of Tyr, a well know place for adventurers. You "+
         "notice a thin layer of desert sand lying over the marble "+
         "square. To your north, the Palace Road is leading to the "+
         "nicer parts of the town, and to your east you see the Temple "+
         "Road, leading past the temple, to the Gladiator arena and "+
         "the slave pits.\n"));
   
   add_prop(ROOM_I_INSIDE, 0);
   
   add_exit(SQUA_D+"square2","west",0);
   add_exit(TEM_STR+"road1","east" );
   add_exit(SQUA_D+"square5","southwest",0);
   add_exit(SQUA_D+"square6","south",0);
   add_exit(PAL_STR+"street1","north" );
   
   add_item(({"temple","temple"}),BSS(
         "You see a large and impressive temple, and you "+
         "recognize it as the well known 'Temple of Tyr'. "+
         "Maybe you should go closer ?\n"));
   add_item(({"arena","arena"}),BSS(
         "You can vaugely see the arena walls in the "+
         "distance, and it looks mighty impressive!\n"));
   add_item(({"square","town square"}),BSS(
         "This square seems to be made of fine "+
         "layed marble rocks. There is a thin layer "+
         "of sand here, but the winds blows away "+
         "all tracks.\n"));
   add_item(({"sand","desert sand"}),BSS(
         "This is usual desert sand that has "+
         "blown in over the city walls. What did "+
         "you expect ?\n"));
   call_out("reset_room", 1);
   
}
