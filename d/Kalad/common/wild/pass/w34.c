/* 
 * /d/Kalad/common/wild/pass/w34.c
 * Purpose    : Valley setting
 * Located    : Hespyre Mountains
 * Created By : Antharanos  
 * Modified By: 
 */ 

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Valley");
   set_long("You are within a wide and open valley.\n"+
      "Giant redwood trees surround you, enfolding you in their vibrant, "+
      "full of life depths. On the sides of the valley, the Hespyre mountains "+
      "tower above the landscape. Their slopes are more gentle here, and as "+
      "such the forest creeps higher up the mountains here than in other "+
      "areas of the range. A huge gash in the side of the mountains is to "+
      "the west.\n");
   add_item(({"huge gash","gash"}),"It is as if a great axe cleaved a "+
      "chunk of the mountainside away, revealing a pass through the mountains.\n");
   add_item(({"giant redwood trees","forest","redwood trees","trees","giant trees","tree"}),
      "The smalles is almost fifteen feet wide at the base, with most of the "+
      "others being as wide as twenty feet. All of them tower hundreds of "+
      "feet into the air, casting dark shadows upon the ground.\n");
   add_item(({"hespyre mountains","mountains","range","mountain"}),
      "Massive formations of rock, so great is their size that everything "+
      "within the landscape is dwarfed in comparison, even the mighty "+
      "redwoods.\n");
   add_item(({"slopes","slope"}),"The relatively gentle slopes of the "+
      "mountains here are covered with a great profusion of redwood trees.\n");
   add_exit("/d/Kalad/common/wild/pass/w35", "west",0,2);
   add_exit("/d/Kalad/common/wild/pass/w36", "north",0,2);
   add_exit("/d/Kalad/common/wild/pass/w33", "south",0,2);
}
