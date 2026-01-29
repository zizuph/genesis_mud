/* Kirk of Port City - Abbey garden
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 1/18/98     Zima        Created
**
*/
#include "defs.h"
inherit  ROOM+"kgardbase";
int      do_step_in();
 
/* room definition */
void create_khalakhor_room() {
   setup_garden_room();
   set_long((query_std_long())+"The entrance to the abbey is to the west, "+
            "marked by a set of concentric stone arches in its wall, "+
            "while the path winds off to the south and east.\n");
 
   add_item(({"entrance","door","doorway","arch","arches"}),
      "A set of pointed arches set inside each other mark the entrance "+
      "of the abbey to the west.\n");
 
   add_exit("kcorr5",  "west", &do_step_in());
   add_exit("kgarden6","east");
   add_exit("kgarden3","south");
}
 
int do_step_in() {
   write("You enter the abbey.\n");
   return 0;
}
