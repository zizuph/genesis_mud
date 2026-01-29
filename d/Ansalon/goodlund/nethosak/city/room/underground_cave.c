#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include <stdproperties.h>
inherit MITHAS_IN;

void
create_mithas_room()
{
   set_short("Underwater cave");
   set_long("@@long_descr");

   add_exit(MROOM + "pirate_leader","north","@@leader_exit",0); 
   add_exit(MROOM + "pirate_cave","east",0,0);
   add_cmd_item(({"water","into water","in water",
       "sea","into sea","in sea","bloodsea","into bloodsea",
       "in bloodsea","hole","into hole","in hole"}),
      ({"enter","dive","jump","step","go"}), "@@into_sea");

   reset_mithas_room();
}

string
long_descr()
{ 
   return "You are standing in a huge undergrown cave, beneth "+
          "the isle of Mithas. The cave must have been made "+
          "by some form of erosion of the stones that form "+
          "the bedrock of the isle. The black rock walls "+
          "are drenched with water and the smell of the fresh "+
          "seawater and wet soil dominate this place. This "+
          "might be a good place to hide ourself or something. "+
          "A small hole in the center of the room is filled "+
          "with seawater and two human-made exits leads to the "+
          "north and east.\n";
}

int
leader_exit()
{
   if (TP->query_name() != CLUBLEADER)
   {
      
      return 1;
   }
   write("You are not allowed to enter this chamber.\n");
   return 0;
}

string
into_sea()
{
    write("You take a deep breath and dive into the " +
      "turbulent waters of the Bloodsea...\n");
    TP->move_living("into the waters of the Blood Bay",
      MROOM + "water2.c", 1, 0);
    return "";
}
