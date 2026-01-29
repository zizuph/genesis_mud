/* File         : /d/Khalakhor/se_speir/plains/room/tfor_c_16.c
 * Creator      : Darragh@Genesis
 * Date         : 01-01-23   
 * Purpose      : 
 * Related Files: 
 * Comments     :
 * Modifications:  
 */

#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include "/d/Khalakhor/sys/defs.h"
#include "plains.h"

inherit "/d/Khalakhor/se_speir/plains/room/tforbase";

int climb_ridge();

int
climb_ridge()
{
   write("With great caution you climb down the steep side of "
       + "the ridge, through a mass of ferns and small bushes, "
       + "and suddenly your descent is at an end.\n");

   TP->move_living("climbing carefully down the ridge, "
                 + "soon disappearing from sight due to the thick "
                 + "vegetation",PLAINS + "rside_05.c",1,0);

   return 1;
}
void
create_khalakhor_room()
{
   create_tforest();

   add_item(({"ridge"}),
              "The ridge is not that high here, a cautious and "
            + "skilled climber should be able to climb down "
            + "there.\n");

   add_exit(PLAINS + "tfor_d_16","south",0,1,1);
   add_exit(PLAINS + "tfor_d_15","southwest",0,1,1);

   add_cmd_item("ridge","climb",climb_ridge);

   set_short("On a ridge in a light forest");
   set_long(query_long() + " Westwards and north of you the forest looks "
                         + "too deep and gloomy, the terrain hostile and "
                         + "unfriendly. Moving in those directions seems "
                         + "hopeless. The ground abruptly drops to the "
                         + "east of you, creating the steep ridge that "
                         + "you stand on. You can hear the sound of a "
                         + "flowing river from the east.\n");
}
