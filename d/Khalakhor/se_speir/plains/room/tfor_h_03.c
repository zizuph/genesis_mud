/* File         : /d/Khalakhor/se_speir/plains/room/tfor_h_02.c
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

   add_exit(PLAINS + "tfor_h_02","west",0,1,1);
   add_exit(PLAINS + "tfor_g_03","north",0,1,1);
   add_exit(PLAINS + "tfor_g_04","northeast",0,1,1);
   add_exit(PLAINS + "tfor_h_04","east",0,1,1);
   add_exit(PLAINS + "tfor_i_04","southeast",0,1,1);
   add_exit(PLAINS + "tfor_i_03","south",0,1,1);
   add_exit(PLAINS + "tfor_i_02","southwest",0,1,1);

   set_long(query_long() + " Northwest of you the forest looks too deep and "
                         + "gloomy, the terrain hostile and unfriendly. "
                         + "Moving in that direction seems hopeless.\n");
}
