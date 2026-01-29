/* File         : /d/Khalakhor/se_speir/plains/room/tfor_k_16.c
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
#include <language.h>
#include <ss_types.h>
#include "/d/Khalakhor/sys/defs.h"
#include "plains.h"

inherit "/d/Khalakhor/se_speir/plains/room/tforbase";

int climb_ridge();

int
climb_ridge()
{
   write("The ridge is too steep, you realise that you would " +
         "probably fall down pretty quick.\n");

    say(QCTNAME(this_player())+ " looks hesitantly down the "
                              + "top of the ridge.\n");
    return 1;
}
void
create_khalakhor_room()
{
   create_tforest();

   add_item(({"plains"}),
              "You can see the plains clearly from within the "
            + "forest, billowing away south towards the sea.\n");
   add_item(({"ridge"}),
              "The ridge is too steep and unsafe to climb down "
            + "at this point.\n");

   add_exit(PLAINS + "tfor_k_15","west",0,1,1);
   add_exit(PLAINS + "tfor_j_15","northwest",0,1,1);
   add_exit(PLAINS + "tfor_j_16","north",0,1,1);
   add_exit(PLAINS + "plains_29_2","south",0,1,1);
   add_exit(PLAINS + "plains_28_2","southwest",0,1,1);

   add_cmd_item("ridge","climb",climb_ridge);

   set_short("On a ridge in a light forest");
   set_long(query_long() + " This is the southern edge of the forest, "
                         + "where the ground abruptly drops to the east "
                         + "of you, creating the steep ridge that you "
                         + "stand on. You can hear the sound of a flowing "
                         + "river far from the east.\n");
}
