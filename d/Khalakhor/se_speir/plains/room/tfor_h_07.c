/* File         : /d/Khalakhor/se_speir/plains/room/tfor_h_07.c
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

   add_exit(PLAINS + "tfor_h_06","west",0,1,1);
   add_exit(PLAINS + "tfor_g_06","northwest",0,1,1);
   add_exit(PLAINS + "tfor_g_07","north",0,1,1);
   add_exit(PLAINS + "tfor_g_08","northeast",0,1,1);
   add_exit(PLAINS + "tfor_h_08","east",0,1,1);
   add_exit(PLAINS + "tfor_i_08","southeast",0,1,1);
   add_exit(PLAINS + "tfor_i_07","south",0,1,1);
   add_exit(PLAINS + "tfor_i_06","southwest",0,1,1);

   set_long(query_long() + " It looks as if it is possible to travel "
                         + "in nearly every direction from here.\n");
}

