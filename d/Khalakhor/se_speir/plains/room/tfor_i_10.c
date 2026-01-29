/* File         : /d/Khalakhor/se_speir/plains/room/tfor_i_10.c
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

   add_exit(PLAINS + "tfor_i_09","west",0,1,1);
   add_exit(PLAINS + "tfor_h_09","northwest",0,1,1);
   add_exit(PLAINS + "tfor_h_10","north",0,1,1);
   add_exit(PLAINS + "tfor_h_11","northeast",0,1,1);
   add_exit(PLAINS + "tfor_i_11","east",0,1,1);
   add_exit(PLAINS + "tfor_j_11","southeast",0,1,1);
   add_exit(PLAINS + "tfor_j_10","south",0,1,1);
   add_exit(PLAINS + "tfor_j_09","southwest",0,1,1);

   set_long(query_long() + " It looks as if it is possible to travel "
                         + "in nearly every direction from here.\n");
}

