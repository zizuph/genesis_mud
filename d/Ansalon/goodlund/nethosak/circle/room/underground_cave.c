/*
 * File Name        : pirate_center_room.c
 * By               : Elmore.
 * Inspiration from : -
 * Date             : Nov. 2000.
 * Description      : Just another guild room :)
 *
 */

#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include "../local.h"
#include <stdproperties.h>
inherit MITHAS_IN;

void
create_mithas_room()
{
   set_short("Underwater cave");
   set_long("@@long_descr");

   add_exit("pirate_center_room","north","@@pirate_exit",0); 
   add_exit("pirate_cave","east",0,0);
   add_cmd_item(({"water","into water","in water",
       "sea","into sea","in sea","bloodsea","into bloodsea",
       "in bloodsea","hole","into hole","in hole"}),
      ({"enter","dive","jump","step","go"}), "@@into_sea");
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
pirate_exit()
{
   if (this_player()->query_guild_name_lay() != "Pirate of the Bloodsea")
   { 
       write("Only pirates are allowed to venture further into the cave "+
             "system.\n");
       return 1;
   }
   return 0;
}

string
into_sea()
{
    write("You take a deep breath and dive into the " +
      "turbulent waters of the Bloodsea...\n");
    this_player()->move_living("into the waters of the Blood Bay",
      MROOM + "sea2.c", 1, 0);
    return "";
}
