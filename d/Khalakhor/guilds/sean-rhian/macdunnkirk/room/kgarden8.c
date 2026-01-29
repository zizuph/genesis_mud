/* Kirk of Port City - Abbey garden
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 1/18/98     Zima        Created
** 3/9/98      Zima        Cedar replace with decorative dogwood
*/
#include "defs.h"
inherit  ROOM+"kgardbase";
 
/* room definition */
void create_khalakhor_room() {
   setup_garden_room();
   set_branchnum(3); // get dogwood branch here instead of ivy
   set_long((query_std_long())+"A rather large flowering tree with "+
            "dark bark grows in the corner of the garden here.\n");
 
   add_item(({"dogwood","tree","dogwood tree"}),
      "It is a large dogwood tree, its top reaching over even the top of "+
      "the kirk. It grows in the very northeast corner of the garden, "+
      "its branches fighting the walls of the kirk to the east and "+
      "of the abbey to the north. Its lowest branches are high above "+
      "your head, and they shade the entire corner. Its dark-bark branches "+
      "are sprinkled with pink four-petal flowers.\n");
   add_item(({"flower","flowers"}),
      "The flowers of the dogwood are four-petaled and a soft pink color. "+
      "They sprinkle bright speckles throughout the dark bark and "+
      "foliage of the tree.\n");
   add_cmd_item(({"flower","flowers"}),"pick",
      "The branches are too high for you to reach them.\n");
   add_exit("kgarden6","south");
   add_exit("kgarden7","west");
}
