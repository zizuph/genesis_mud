/* File         : /d/Khalakhor/se_speir/plains/room/tfor_g_08.c
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

   add_exit(PLAINS + "tfor_g_07","west",0,1,1);
   add_exit(PLAINS + "tfor_f_07","northwest",0,1,1);
   add_exit(PLAINS + "tfor_g_09","east",0,1,1);
   add_exit(PLAINS + "tfor_h_09","southeast",0,1,1);
   add_exit(PLAINS + "tfor_h_08","south",0,1,1);
   add_exit(PLAINS + "tfor_h_07","southwest",0,1,1);

   set_long(query_long() + " Northwards of you the forest looks too deep and "
                         + "gloomy, the terrain hostile and unfriendly. "
                         + "Moving in those directions seems hopeless.\n");
}
