/* File         : /d/Khalakhor/se_speir/plains/room/tfor_i_02.c
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

   add_exit(PLAINS + "tfor_i_01","west",0,1,1);
   add_exit(PLAINS + "tfor_h_02","north",0,1,1);
   add_exit(PLAINS + "tfor_h_03","northeast",0,1,1);
   add_exit(PLAINS + "tfor_i_03","east",0,1,1);
   add_exit(PLAINS + "tfor_j_03","southeast",0,1,1);
   add_exit(PLAINS + "tfor_j_02","south",0,1,1);
   add_exit(PLAINS + "tfor_j_01","southwest",0,1,1);

   set_long(query_long() + " Northwest of you the forest looks too deep and "
                         + "gloomy, the terrain hostile and unfriendly. "
                         + "Moving in that direction seems hopeless.\n");

}
