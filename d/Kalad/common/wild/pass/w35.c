/* 
 * /d/Kalad/common/wild/pass/w35.c
 * Purpose    : Mountain setting
 * Located    : North in Hespyre Mountains
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
   set_short("Mountain Pass");
   set_long("You are within a narrow pass in the depths of the Hespyre "+
      "mountains. Only a few redwoods grow here, and they are relatively "+
      "diminutive in comparison to the majority that grow elsewhere. All "+
      "about you are the imposing masses of the cliff walls, many of which "+
      "hang over this pass, threatening to fall down upon you.\n");
   add_item(({"hespyre mountains","mountains","mountain"}),"The towering "+
      "peaks of the range seem to scrape the sky itself, so great is their "+
      "height. The entire pass is covered in shadows, due to this same fact.\n");
   add_item(({"redwoods","redwood"}),"The trees here are only ten or so "+
      "feet wide and a few dozen feet in height, quite unimpressive for "+
      "redwoods.\n");
   add_item(({"cliff walls","walls","cliff wall","wall"}),"The sides of "+
      "mountains are almost vertical in alignment, while others are so steep "+
      "that they actually hang over the pass, blocking out the sky and casting "+
      "dark shadows across the pass.\n");
   add_exit("/d/Kalad/common/wild/pass/w25", "northwest",0,2);
   add_exit("/d/Kalad/common/wild/pass/w34", "east",0,2);
}
