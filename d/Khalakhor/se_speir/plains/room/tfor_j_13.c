/* File         : /d/Khalakhor/se_speir/plains/room/tfor_j_13.c
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

   add_item(({"path"}),
              "This small path looks very old, and is completely "
            + "overgrown in some places, but you can follow it "
            + "to the south. When looking in the other directions, "
            + "you don't see a trace of the path. Whoever has been "
            + "using it has not gone far into the woods.\n");

   add_exit(PLAINS + "tfor_j_12","west",0,1,1);
   add_exit(PLAINS + "tfor_i_12","northwest",0,1,1);
   add_exit(PLAINS + "tfor_i_13","north",0,1,1);
   add_exit(PLAINS + "tfor_i_14","northeast",0,1,1);
   add_exit(PLAINS + "tfor_j_14","east",0,1,1);
   add_exit(PLAINS + "tfor_k_14","southeast",0,1,1);
   add_exit(PLAINS + "tfor_k_13","south",0,1,0);
   add_exit(PLAINS + "tfor_h_12","southwest",0,1,1);

   set_short("On a small path in a light forest");
   set_long(query_long() + " You are on a small path at the southern "
                         + "edge of the forest.\n");
}
