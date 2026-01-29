/* File         : /d/Khalakhor/se_speir/plains/room/tfor_k_02.c
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

   add_exit(PLAINS + "tfor_j_01","northwest",0,1,1);
   add_exit(PLAINS + "tfor_j_02","north",0,1,1);
   add_exit(PLAINS + "tfor_j_03","northeast",0,1,1);
   add_exit(PLAINS + "tfor_k_03","east",0,1,1);
   add_exit(PLAINS + "plains_16_2","southeast",0,1,1);
   add_exit(PLAINS + "plains_15_2","south",0,1,1);

   set_long(query_long() + " You are at the southern edge of the forest.\n");
}
