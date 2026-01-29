/* File         : /d/Khalakhor/se_speir/plains/room/tfor_k_04.c
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

void
create_khalakhor_room()
{
   create_tforest();

   add_item(({"plains"}),
              "You can see the plains clearly from within the "
            + "forest, billowing away south towards the sea.\n");
   add_item(({"path"}),
              "This small path looks very old, and is completely "
            + "overgrown in some places, but you can follow it "
            + "out of the woods to the southwest or deeper into "
            + "the forest north.\n");

   add_exit(PLAINS + "tfor_k_03","west",0,1,1);
   add_exit(PLAINS + "tfor_j_03","northwest",0,1,1);
   add_exit(PLAINS + "tfor_j_04","north",0,1,0);
   add_exit(PLAINS + "tfor_j_05","northeast",0,1,1);
   add_exit(PLAINS + "tfor_k_05","east",0,1,1);
   add_exit(PLAINS + "plains_18_2","southeast",0,1,1);
   add_exit(PLAINS + "plains_17_2","south",0,1,1);
   add_exit(PLAINS + "plains_16_2","southwest",0,1,0);

   set_short("On a small path in a light forest");
   set_long(query_long() + " You are on a small path at the southern "
                         + "edge of the forest.\n");
}
